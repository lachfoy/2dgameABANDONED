
#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

class GameStateManager
{
public:
    //GameStateManager() {}
    //~GameStateManager() {}

    enum GameState { // should be private
        GAMESTATE_DEFAULT,
        GAMESTATE_PAUSED
    };

    inline GameState getGameState() const { return m_gameState; } // dont use probably lol
    
    inline bool getPaused() const { return (m_gameState == GAMESTATE_PAUSED); }

    void togglePaused()
    {
        m_gameState = (m_gameState == GAMESTATE_PAUSED) ? GAMESTATE_DEFAULT : GAMESTATE_PAUSED;
    }

    void setGameState(GameState& gameState) { m_gameState = gameState; } // also dont use probably

private:
    GameState m_gameState;

};

#endif