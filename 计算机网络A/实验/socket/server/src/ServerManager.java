import java.util.List;
import java.util.Scanner;

/**
 * @author SoundOfAutumn
 * @date 2024/9/9 18:06
 */
public class ServerManager {
    private final List<Server> servers = List.of(new TCPServer(), new UDPServer());

    private final ServerProcessor processor = new DefaultServerProcessor();

    public void run(String[] args) {
        processor.setBroadcast(this::broadcast);
        for (final Server server : servers) {
            server.parseArgs(args);
            server.setProcessor(processor);
            if (!server.start()) {
                System.err.println("Failed to start server");
            }
        }
    }

    public void broadcast(String message, String client) {
        for (final Server server : servers) {
            server.broadcast(message, client);
        }
    }

    public void stop() {
        for (final Server server : servers) {
            if (!server.stop()) {
                System.err.println("Failed to stop server");
            }
        }
        System.out.println("Server stopped");
    }

    public void commandLoop() {
        System.out.println("Usage: online, kick <client>, exit");
        final Scanner scanner = new Scanner(System.in);
        while (true) {
            final String command = scanner.nextLine();
            if (command.equals("exit")) {
                break;
            }
            if (command.equals("online")) {
                System.out.println(processor.getOnlineClients());
            }
            if (command.startsWith("kick")) {
                final String[] split = command.split(" ");
                if (split.length == 2) {
                    if (processor.kick(split[1])) {
                        System.out.println("Client kicked");
                    } else {
                        System.err.println("Failed to kick client");
                    }
                }
            }
        }
    }
}
