/**
 * 客户端通信接口
 * 负责连接服务器，发送消息，接收消息
 * 分别实现TCP和UDP两种通信方式
 *
 * @author SoundOfAutumn
 * @date 2024/9/2 15:53
 */
public interface Client {

    boolean connect();

    boolean close();

    void run(ClientProcessor processor);

    void setAddress(String address);

    void setPort(int port);

    default void parseArgs(String[] args) {
        for (int i = 0; i < args.length; i++) {
            if (args[i].equals("-i")) {
                setAddress(args[++i]);
            }
            if (args[i].equals("-p")) {
                setPort(Integer.parseInt(args[++i]));
            }
        }
    }
}
