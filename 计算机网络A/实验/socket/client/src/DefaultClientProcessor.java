import java.util.Scanner;

/**
 * @author SoundOfAutumn
 * @date 2024/9/2 17:54
 */
public class DefaultClientProcessor implements ClientProcessor {

    private final Scanner scanner = new Scanner(System.in);

    private volatile boolean waitForResponse = false;

    private final Object lock = new Object();

    private String username;

    private boolean isLogin = false;

    @Override
    public void showUsage() {
        System.out.println("Usage:");
        System.out.println("login <username> <password>");
        System.out.println("register <username> <password>");
        System.out.println("echo <message>");
        System.out.println("exit");
    }

    private String processCommand(String commandStr) {
        final String[] commandStrs = commandStr.split(" ");
        if (commandStr.startsWith("login")) {
            if (commandStrs.length != 3) {
                System.out.println("Usage: login <username> <password>");
                return null;
            }
            username = commandStrs[1];
            return "login " + commandStrs[1] + " " + commandStrs[2];
        } else if (commandStr.startsWith("register")) {
            if (commandStrs.length != 3) {
                System.out.println("Usage: register <username> <password>");
                return null;
            }
            return "register " + commandStrs[1] + " " + commandStrs[2];
        } else if (commandStr.startsWith("echo")) {
            if (!isLogin) {
                System.out.println("Please login first.");
                return null;
            }
            if (commandStrs.length < 2) {
                System.out.println("Usage: echo <message>");
                return null;
            }
            return "echo " + username + " " + commandStrs[1];
        } else if (commandStr.startsWith("exit")) {
            return "exit";
        } else {
            System.out.println("unknown command");
        }
        return null;
    }

    private void waitUtilResponse() {
        if (!waitForResponse) {
            return;
        }
        synchronized (lock) {
            try {
                lock.wait();
            } catch (InterruptedException e) {
                return;
            }
        }
    }

    @Override
    public String send() {
        waitUtilResponse();
        while (true) {
            final String commandStr = scanner.nextLine();
            final String result = processCommand(commandStr);
            if ("exit".equals(result)) {
                return null;
            }
            waitForResponse = true;
            if (result != null) {
                return result;
            }
        }
    }

    @Override
    public void receive(String message) {
        if (waitForResponse) {
            synchronized (lock) {
                lock.notify();
                waitForResponse = false;
            }
        }
        if (message.startsWith("login success")) {
            isLogin = true;
        } else if (message.startsWith("login failed")) {
            isLogin = false;
        }
        if (!message.startsWith("unknown command")) {
            System.out.println(message);
        }
    }
}
