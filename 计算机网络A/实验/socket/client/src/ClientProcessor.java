/**
 * 客户端消息处理器接口
 * 定义了客户端消息处理器的基本功能
 * 通过加锁来保证先收到指令的结果后再发送指令
 *
 * @author SoundOfAutumn
 * @date 2024/9/2 16:01
 */
public interface ClientProcessor {

    void showUsage();

    String send();

    void receive(String message);
}
