import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

/**
 * @author SoundOfAutumn
 * @date 2024/9/2 19:56
 */
public class UDPClient implements Client {

    private String address = "127.0.0.1";

    private int port = 8080;

    private volatile boolean isRunning = false;

    private DatagramSocket socket;

    @Override
    public void setAddress(String address) {
        this.address = address;
    }

    @Override
    public void setPort(int port) {
        this.port = port;
    }

    @Override
    public boolean connect() {
        isRunning = true;
        try {
            socket = new DatagramSocket();
        } catch (SocketException e) {
            return false;
        }
        return true;
    }

    @Override
    public boolean close() {
        isRunning = false;
        if (socket != null) {
            socket.close();
        }
        socket = null;
        return true;
    }

    private void process(ClientProcessor processor) {
        final String sendMsg = processor.send();
        if (sendMsg == null) {
            isRunning = false;
            return;
        }
        try {
            final byte[] sendBuffer = sendMsg.getBytes();
            final DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, InetAddress.getByName(address), port);
            socket.send(sendPacket);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void run(ClientProcessor processor) {
        final Thread receiveThread = new Thread(() -> {
            while (isRunning) {
                try {
                    final byte[] receiveBuffer = new byte[1024];
                    final DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
                    socket.receive(receivePacket);
                    final String receiveMsg = new String(receivePacket.getData(), 0, receivePacket.getLength());
                    processor.receive(receiveMsg);
                } catch (IOException e) {
                    if (!isRunning) {
                        return;
                    }
                    throw new RuntimeException(e);
                }
            }
        });
        receiveThread.start();
        processor.showUsage();
        while (isRunning) {
            process(processor);
        }
    }


}
