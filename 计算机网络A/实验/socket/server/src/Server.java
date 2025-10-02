/**
 * 服务端接口
 * 负责启动服务端，停止服务端，广播消息
 * TCP实现通过ServerSocket处理客户端连接，同时通过线程池处理多个客户端连接
 * UDP实现通过DatagramSocket处理客户端连接
 *
 * @author SoundOfAutumn
 * @date 2024/9/2 16:17
 */
public interface Server {

    void setPort(int port);

    int getPort();

    default void parseArgs(String[] args) {
        for (int i = 0; i < args.length; i++) {
            if (args[i].equals("-p")) {
                setPort(Integer.parseInt(args[++i]));
            }
        }
    }

    void setProcessor(ServerProcessor processor);

    void broadcast(String message, String client);

    boolean start();

    boolean stop();

    String getProtocol();

    boolean isRunning();
}
