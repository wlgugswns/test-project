#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

namespace Musoeun {
    class Object;

    class Component {
    public:
        virtual ~Component() {}
        virtual void Start() {}
        virtual void Update() {}
    };

    class Object {
    private:
        int x;
        int y;
        float scale;
        float rotation;
        std::vector<Component*> components;

    public:
        Object(int x, int y) : x(x), y(y), scale(1.0f), rotation(0.0f) {}

        void AddComponent(Component* component) {
            components.push_back(component);
        }

        void Render() {
            for (Component* component : components) {
                component->Update();
            }
            // Rendering code for the object's shape using the provided ScreenBuffer
            std::cout << "Rendering object at (" << x << ", " << y << ")" << std::endl;
        }

        ~Object() {
            for (Component* component : components) {
                delete component;
            }
        }
    };

    class Scene {
    private:
        int screenWidth;
        int screenHeight;
        std::vector<Object*> objects;

    public:
        Scene(int width, int height) : screenWidth(width), screenHeight(height) {}

        void AddObject(Object* object) {
            objects.push_back(object);
        }

        void Draw() {
            InitScreenBuf();
            for (Object* object : objects) {
                object->Render();
            }
            DrawScreenBuf(); // Call the new function to draw the screen buffer
        }

        void InitScreenBuf() {
            // Code to initialize the screen buffer
            std::cout << "Initializing screen buffer" << std::endl;
        }

        void ClearScreenBuf() {
            // Clear the console screen using Windows API
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD coordScreen = { 0, 0 };
            DWORD cCharsWritten;
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            DWORD dwConSize;

            GetConsoleScreenBufferInfo(hConsole, &csbi);
            dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

            FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
            GetConsoleScreenBufferInfo(hConsole, &csbi);
            FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

            SetConsoleCursorPosition(hConsole, coordScreen);
        }

        void DrawScreenBuf() {
            // Rendering code to draw the ScreenBuffer on the screen
            std::cout << "Drawing screen buffer" << std::endl;
        }

        class CustomComponent : public Component {
        public:
            void Start() override {
                std::cout << "CustomComponent Start" << std::endl;
            }

            void Update() override {
                std::cout << "CustomComponent Update" << std::endl;
            }
        };

        class SnakeBody : public Object {
        public:
            SnakeBody(int x, int y) : Object(x, y) {}
        };

        void StartGame()
        {
            ClearScreenBuf();

            // Rendering code for the game screen using the provided ScreenBuffer

            const int screenWidth = 50;
            const int screenHeight = 20;

            // Output the top border
            for (int i = 0; i < screenWidth; ++i) {
                std::cout << ANSI_COLOR_MAGENTA"+";
            }
            std::cout << std::endl;

            // Output the middle section
            for (int i = 0; i < screenHeight - 2; ++i) {
                std::cout << ANSI_COLOR_YELLOW"+";
                for (int j = 0; j < screenWidth - 2; ++j) {
                    std::cout << " ";
                }
                std::cout << "+" << std::endl;
            }

            // Output the bottom border
            for (int i = 0; i < screenWidth; ++i) {
                std::cout << ANSI_COLOR_MAGENTA"+";
            }
            std::cout << std::endl;

            std::cout << ANSI_COLOR_RESET"���� �޴��� ���ư����� ESC Ű�� �����ּ���." << std::endl;

            bool returnToMainMenu = false;
            bool clearGameScreen = false;

            while (!returnToMainMenu) {
                if (_kbhit()) {
                    char keyPressed = _getch();
                    if (keyPressed == 27) {
                        std::cout << "���� �޴��� ���ư��ðڽ��ϱ�? (Y/N): ";
                        char choice = _getch();
                        std::cout << std::endl;
                        if (choice == 'Y' || choice == 'y') {
                            returnToMainMenu = true;
                            break;
                        }
                        else if (choice == 'N' || choice == 'n') {
                            clearGameScreen = true;
                        }
                    }
                }

                if (clearGameScreen) {
                    ClearScreenBuf();
                    clearGameScreen = false;

                    // Output the game border and message again
                    for (int i = 0; i < screenWidth; ++i) {
                        std::cout << ANSI_COLOR_MAGENTA"+";
                    }
                    std::cout << std::endl;

                    for (int i = 0; i < screenHeight - 2; ++i) {
                        std::cout << "+";
                        for (int j = 0; j < screenWidth - 2; ++j) {
                            std::cout << " ";
                        }
                        std::cout << "+" << std::endl;
                    }

                    for (int i = 0; i < screenWidth; ++i) {
                        std::cout << "+";
                    }
                    std::cout << std::endl;

                    std::cout << ANSI_COLOR_RESET"���� �޴��� ���ư����� ESCŰ�� �����ּ���." << std::endl;
                }
            }
        }

        void DisplayGameInstructions()
        {
            ClearScreenBuf();

            std::cout << ANSI_COLOR_YELLOW"������ ����� Snake Bite �����Դϴ�." << std::endl;
            std::cout << ANSI_COLOR_RED"�Ӹ��� �ʹ� ������." << std::endl;
            std::cout << ANSI_COLOR_RESET"���� �޴��� ���ư����� ESC Ű�� �����ּ���." << std::endl;

            bool returnToMainMenu = false;

            while (!returnToMainMenu) {
                if (_kbhit()) {
                    char keyPressed = _getch();
                    if (keyPressed == 27) { // Check if ESC key is pressed
                        returnToMainMenu = true;
                    }
                }
            }
        }

        void DisplayGameRankings()
        {
            ClearScreenBuf();

            std::cout << "���� ��ŷ :" << std::endl;
            std::cout << ANSI_COLOR_RED"���� �� �� �����..." << std::endl;
            std::cout << ANSI_COLOR_RESET"���� �޴��� ���ư����� ESC Ű�� �����ּ���." << std::endl;

            bool returnToMainMenu = false;

            while (!returnToMainMenu) {
                if (_kbhit()) {
                    char keyPressed = _getch();
                    if (keyPressed == 27) { // Check if ESC key is pressed
                        returnToMainMenu = true;
                    }
                }
            }
        }

        void MainMenu()
        {
            int choice;

            while (true) {
                ClearScreenBuf();

                Object* object1 = new Object(100, 100);
                object1->AddComponent(new CustomComponent());

                Object* object2 = new SnakeBody(200, 200);
                object2->AddComponent(new CustomComponent());

                AddObject(object1);
                AddObject(object2);

                ClearScreenBuf();

                // Rendering code for the main menu screen using the provided ScreenBuffer
                std::cout << ANSI_COLOR_YELLOW"�� ��" << std::endl;
                std::cout << ANSI_COLOR_RESET"1. ���� ����" << std::endl;
                std::cout << "2. ���� ����" << std::endl;
                std::cout << "3. ���� ��ŷ" << std::endl;
                std::cout << "4. ���� ����" << std::endl;
                std::cout << "���ϴ� ��ȣ ������ Enter: ";
                std::cin >> choice;

                switch (choice) {
                case 1:
                    StartGame();
                    break;
                case 2:
                    DisplayGameInstructions();
                    break;
                case 3:
                    DisplayGameRankings();
                    break;
                case 4:
                    std::cout << "������ �����ϴ�." << std::endl;
                    delete object1;
                    delete object2;
                    return;
                default:
                    std::cout << "�߸��� �����Դϴ�. �ٽ� �õ��� �ּ���." << std::endl;
                    break;
                }

                std::cout << "�ƹ� Ű�� �����ּ���.";
                _getch();

                delete object1;
                delete object2;
            }
        }
    };   
}