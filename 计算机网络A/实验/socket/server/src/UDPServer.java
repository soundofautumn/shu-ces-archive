import java.io.IOException;
import java.net.*;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * @author SoundOfAutumn
 * @date 2024/9/2 20:06
 */
public class UDPServer extends AbstractServer {

    private DatagramSocket socket;

    private final List<SocketAddress> clients = new CopyOnWriteArrayList<>();

    @Override
    public boolean start() {
        try {
            socket = new DatagramSocket(getPort());
        } catch (SocketException e) {
            return false;
        }
        return super.start();
    }

    @Override
    public boolean stop() {
        if (!super.stop()) {
            return false;
        }
        socket.close();
        return true;
    }

    @Override
    public String getProtocol() {
        return "UDP";
    }

    void accept() {
        try {
            final byte[] receiveBuffer = new byte[1024];
            final DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
            socket.receive(receivePacket);
            System.out.println("Received packet from " + receivePacket.getSocketAddress());
            if (clients.stream().noneMatch(client -> client.equals(receivePacket.getSocketAddress()))) {
                clients.add(receivePacket.getSocketAddress());
            }
            final String client = receivePacket.getSocketAddress().toString();
            final String receiveMsg = new String(receivePacket.getData(), 0, receivePacket.getLength());
            System.out.println(client + " -> " + receiveMsg);
            final String sendMsg = getProcessor().process(client, receiveMsg);
            System.out.println(client + " <- " + sendMsg);
            final byte[] sendBuffer = sendMsg.getBytes();
            final DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, receivePacket.getAddress(), receivePacket.getPort());
            socket.send(sendPacket);
        } catch (IOException e) {
            if (!isRunning()) {
                return;
            }
            throw new RuntimeException(e);
        }

    }

    @Override
    public void broadcast(String message, String client) {
        System.out.println("UDP Server received broadcast request from " + client + ": " + message);
        final byte[] sendBuffer = message.getBytes();
        clients.stream()
                .filter(address -> !address.toString().equals(client))
                .forEach(address -> {
                    final DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, address);
                    try {
                        System.out.println(address + " <- " + message);
                        socket.send(sendPacket);
                    } catch (IOException e) {
                        System.err.println("Failed to broadcast message to " + socket.getRemoteSocketAddress().toString());
                        clients.remove(address);
                        getProcessor().removeClient(address.toString());
                        return;
                    }
                });
    }
}
