#ifndef GAME_HH
#define GAME_HH

#include "deck.hh"
#include "player.hh"
#include "dealer.hh"

class Game
{
public:
    /**
     * @brief Game constructor
     */
    Game();

    /**
     * @brief Game destructor
     */
    ~Game();

    /**
     * @brief play
     */
    void new_round();

    /**
     * @brief get_player_hand
     */
    const std::vector<std::unique_ptr<Card>>& get_player_hand();

    /**
     * @brief get_dealer_hand
     */
    const std::vector<std::unique_ptr<Card>>& get_dealer_hand();

    /**
     * @brief get_player_points
     */
    int get_player_points();

    /**
     * @brief get_player_points
     */
    int get_player_secondary_points();

    /**
     * @brief get_dealer_points
     */
    int get_dealer_points();

    /**
     * @brief get_winner
     */
    std::string get_winner();

    /**
     * @brief Dealers turn to play
     */
    void dealer_turn();

    /**
     * @brief Players turn to play
     */
    void player_hit();

    /**
     * @brief Check if player has blackjack
     */
    bool is_blackjack_player();

    /**
     * @brief Check if dealer has blackjack
     */
    bool is_blackjack_dealer();

    /**
     * @brief Check if player is over
     */
    bool is_player_over();

    /**
     * @brief Check if dealer is over
     */
    bool is_dealer_over();

    /**
     * @brief Reset the game
     */
    void reset_game();


private:
    std::unique_ptr<Deck> deck_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<Dealer> dealer_;
    bool player_won_ = false;
    bool dealer_won_ = false;
    bool tie_ = false;
    bool round_over_ = false;

    static const int BLACKJACK_THRESHOLD = 21;

    /**
     * @brief Dealers turn to play
     */
    void initial_draw();

    /**
     * @brief Determine the winner of the game
     */
    void determine_winner();

};

#endif // GAME_HH
