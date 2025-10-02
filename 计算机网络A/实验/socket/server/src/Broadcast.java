/**
 * @author SoundOfAutumn
 * @date 2024/9/9 18:09
 */
@FunctionalInterface
public interface Broadcast {
    void broadcast(String message, String client);
}
