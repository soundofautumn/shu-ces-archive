import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * @author SoundOfAutumn
 * @date 2024/9/2 16:16
 */
public class TCPServer extends AbstractServer {

    private ServerSocket serverSocket;

    private final List<Socket> clients = new CopyOnWriteArrayList<>();

    private final ThreadPoolExecutor executor = new ThreadPoolExecutor(
            10,
            10,
            1,
            TimeUnit.SECONDS,
            new ArrayBlockingQueue<>(10),
            r -> new Thread(r, "TCP-Server-Thread"),
            new ThreadPoolExecutor.DiscardPolicy()
    );

    @Override
    public boolean start() {
        try {
            serverSocket = new ServerSocket(getPort());
        } catch (IOException e) {
            return false;
        }
        return super.start();
    }

    @Override
    public boolean stop() {
        if (!super.stop()) {
            return false;
        }

        try {
            for (Socket client : clients) {
                client.close();
            }
            serverSocket.close();
        } catch (IOException e) {
            return false;
        }
        executor.shutdown();
        boolean isTerminated;
        try {
            isTerminated = executor.awaitTermination(1, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            return false;
        }
        if (!isTerminated) {
            executor.shutdownNow();
        }
        return true;
    }

    @Override
    public String getProtocol() {
        return "TCP";
    }

    @Override
    void accept() {
        try {
            final Socket socket = serverSocket.accept();
            final String client = socket.getRemoteSocketAddress().toString();
            clients.add(socket);
            System.out.println("TCP Client connected: " + client);
            executor.execute(() -> {
                try {
                    final BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    final BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                    while (isRunning()) {
                        final String receiveMsg = in.readLine();
                        if (receiveMsg == null) {
                            break;
                        }
                        System.out.println(client + " -> " + receiveMsg);
                        final String sendMsg = getProcessor().process(client, receiveMsg);
                        System.out.println(client + " <- " + sendMsg);
                        out.write(sendMsg);
                        out.newLine();
                        out.flush();
                    }
                    socket.close();
                    System.out.println("TCP Client disconnected: " + client);
                    clients.remove(socket);
                    getProcessor().removeClient(client);
                } catch (IOException e) {
                    if (!isRunning()) {
                        return;
                    }
                    throw new RuntimeException(e);
                } finally {
                    getProcessor().kick(client);
                }
            });
        } catch (IOException e) {
            if (!isRunning()) {
                return;
            }
            throw new RuntimeException(e);
        }
    }

    @Override
    public void broadcast(String message, String client) {
        System.out.println("TCP Server received broadcast request from " + client + ": " + message);
        clients.stream()
                .filter(socket -> !socket.getRemoteSocketAddress().toString().equals(client))
                .forEach(socket -> {
                    try {
                        System.out.println(socket.getRemoteSocketAddress() + " <- " + message);
                        final BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                        out.write(message);
                        out.newLine();
                        out.flush();
                    } catch (IOException e) {
                        System.err.println("Failed to broadcast message to " + socket.getRemoteSocketAddress().toString());
                        return;
                    }
                });
    }
}
