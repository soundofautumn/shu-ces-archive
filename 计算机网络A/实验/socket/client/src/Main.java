/**
 * @author SoundOfAutumn
 * @date 2024/9/2 14:59
 */
public class Main {

    private static void checkArgs(String[] args) {
        for (int i = 0; i < args.length; i++) {
            if (args[i].startsWith("-")) {
                if (i + 1 >= args.length || args[i + 1].startsWith("-")) {
                    System.out.println("Invalid argument: " + args[i]);
                    System.exit(1);
                }
            }
        }
    }

    public static void main(String[] args) {
        checkArgs(args);
        Client client = null;
        if (args.length < 1) {
            System.out.println("Usage: java -jar client.jar <protocol> [-h host] [-p port]");
            System.exit(1);
        }
        if (args[0].equalsIgnoreCase("udp")) {
            client = new UDPClient();
        } else if (args[0].equalsIgnoreCase("tcp")) {
            client = new TCPClient();
        } else {
            System.out.println("Invalid protocol: " + args[0]);
            System.exit(1);
        }
        client.parseArgs(args);
        if (!client.connect()) {
            System.out.println("Failed to connect to server");
            return;
        }
        client.run(new DefaultClientProcessor());
        if (!client.close()) {
            System.out.println("Failed to close connection");
        }
    }
}