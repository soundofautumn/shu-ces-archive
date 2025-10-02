import java.util.Collection;

/**
 * 服务端处理器
 * 负责处理客户端请求
 * 服务端处理器应该是线程安全的
 * 通过使用线程安全的集合类如ConcurrentHashMap来存储数据来保证线程安全
 *
 * @author SoundOfAutumn
 * @date 2024/9/2 16:17
 */
public interface ServerProcessor {

    void setBroadcast(Broadcast broadcast);

    String process(String client, String message);

    Collection<String> getOnlineClients();

    boolean kick(String username);

    boolean removeClient(String client);
}
