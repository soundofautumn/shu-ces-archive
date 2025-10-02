import java.io.*;
import java.net.InetAddress;
import java.net.Socket;

/**
 * @author SoundOfAutumn
 * @date 2024/9/2 15:07
 */
public class TCPClient implements Client {

    private String address = "127.0.0.1";

    private int port = 8080;

    private volatile boolean isRunning = false;

    private Socket socket;

    private BufferedReader reader;

    private BufferedWriter writer;

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
        try {
            socket = new Socket(InetAddress.getByName(address), port);
            reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            isRunning = true;
        } catch (IOException e) {
            return false;
        }
        return true;
    }

    @Override
    public boolean close() {
        try {
            socket.close();
            isRunning = false;
        } catch (IOException e) {
            return false;
        }
        return true;
    }

    private void process(ClientProcessor processor) {
        final String sendMsg = processor.send();
        if (sendMsg == null) {
            isRunning = false;
            return;
        }
        try {
            writer.write(sendMsg);
            writer.newLine();
            writer.flush();
        } catch (IOException e) {
            if (socket.isClosed()) {
                isRunning = false;
                return;
            }
            throw new RuntimeException(e);
        }
    }

    @Override
    public void run(ClientProcessor processor) {
        final Thread receiveThread = new Thread(() -> {
            while (isRunning) {
                try {
                    final String receiveMsg = reader.readLine();
                    if (receiveMsg == null) {
                        isRunning = false;
                        break;
                    }
                    processor.receive(receiveMsg);
                } catch (IOException e) {
                    if (socket.isClosed()) {
                        isRunning = false;
                        break;
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
