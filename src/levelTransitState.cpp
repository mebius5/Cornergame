#include <state.h>
#include <sstream>

LevelTransitState::LevelTransitState(int windowW, int windowH, EntityManager &entityManager,
                                     std::vector<Command *> &commandList, SDL_Renderer *renderer,
                                     DrawingHandler &drawingHandler, InputHandler &inputHandler,
                                     SoundHandler &soundHandler, ControlHandler &controlHandler):
        State(entityManager, commandList, renderer, windowW, windowH),
        drawingHandler(drawingHandler),
        inputHandler(inputHandler),
        soundHandler(soundHandler),
        controlHandler(controlHandler)
{
}

void LevelTransitState::begin(int level) {
    this->soundHandler.playBackgroundMusic(MUSIC_HIGHSCORE);

    readTransitString(level);

    if(this->transitionText.length()==0){
        std::cerr << "Level text did not contain any string" << std::endl;
        return;
    }

    this->entityManager.createHorizontallyCenteredFadeInText(
            FONT_GLOBAL, this->transitionText.c_str(),
            80, 255, 255, 255, 0, this->windowW, 100
    );
}

void LevelTransitState::readTransitString(int level) {


    std::stringstream str;

    std::string filename = "./levels/level";
    filename.append(std::to_string(level));
    filename.append("_text.txt");

    std::ifstream ifs(filename);
    if(!ifs.is_open()){
        std::cerr << "Cannot open level file: " << filename << std::endl;
        return ;
    }

    while(ifs.peek() != EOF)
    {
        str << (char) ifs.get();
    }
    ifs.close();
    this->transitionText = str.str();
    str.clear();
}

StateEnum LevelTransitState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();
    int timeElapsed = 0;

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = (int) (currentTime - lastTime);
        lastTime = currentTime;
        timeElapsed+=dt;

        this->inputHandler.handleEvents(dt);
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState != STATE_NONE)
            return nextState;

        if(this->controlHandler.isPreviewOff())
            break;

        if (timeElapsed > 5000) {   //Return to Play screen after 5 secs
            break;
        }
    }

    return STATE_PLAY;
}

void LevelTransitState::cleanup(StateEnum /*next*/) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
}


int LevelTransitState::nextLevel() {
    return 0;
}
