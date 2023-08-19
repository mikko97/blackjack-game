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
     * @brief Get the hand of the player
     * @return Reference to the vector containing the pointers to the card objects
     */
    const std::vector<std::unique_ptr<Card>>& get_player_hand();

    /**
     * @brief Get the hand of the dealer
     * @return Reference to the vector containing the pointers to the card objects
     */
    const std::vector<std::unique_ptr<Card>>& get_dealer_hand();

    /**
     * @brief Get the points of the player
     * @return Players points
     */
    int get_player_points();

    /**
     * @brief Get the secondary points of the player if ace is dealt
     * @return Players secondary points
     */
    int get_player_secondary_points();

    /**
     * @brief Get the points of the dealer
     * @return Dealers points
     */
    int get_dealer_points();

    /**
     * @brief Get the winner of the game
     * @return String implicating the winner, or tie
     */
    std::string get_winner();

    /**
     * @brief Dealers turn to play
     */
    void dealer_turn();

    /**
     * @brief Players drawing of a card
     */
    void player_hit();

    /**
     * @brief Check if player has blackjack
     * @return True or false
     */
    bool is_blackjack_player();

    /**
     * @brief Check if dealer has blackjack
     * @return True or false
     */
    bool is_blackjack_dealer();

    /**
     * @brief Check if player is over
     * @return True or false
     */
    bool is_player_over();

    /**
     * @brief Check if dealer is over
     * @return True or false
     */
    bool is_dealer_over();

    /**
     * @brief Reset the game
     */
    void reset_game();

    /**
     * @brief Get the number of cards left in the deck
     * @return The number of cards left
     */
    int get_deck_size();


private:
    /**
     * @brief Draw the initial cards for player and dealer
     */
    void initial_draw();

    /**
     * @brief Determine the winner of the game
     */
    void determine_winner();

    std::unique_ptr<Deck> deck_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<Dealer> dealer_;
    bool player_won_ = false;
    bool dealer_won_ = false;
    bool tie_ = false;
    bool round_over_ = false;

    static const int BLACKJACK_THRESHOLD = 21;
};

#endif // GAME_HH
