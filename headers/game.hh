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
     * @brief Reset parameters for new round of blackjack
     */
    void new_round();

    /**
     * @brief New round for player
     * @return bool value if initial draw was succesful
     */
    bool new_round_player();

    /**
     * @brief New round for dealer
     * @return bool value if initial draw was succesfu
     */
    bool new_round_dealer();

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
     * @return Bool value if deck has cards left to draw
     */
    bool dealer_turn();

    /**
     * @brief Players drawing of a card
     * @return Bool value if deck has cards left to draw
     */
    bool player_hit();

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
     * @brief Get the number of cards left in the deck
     * @return The number of cards left
     */
    int get_deck_size();

    /**
     * @brief Create a new deck
     */
    void create_new_deck();


private:

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
