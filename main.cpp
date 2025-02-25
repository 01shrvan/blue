#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <tuple>
#include <iomanip>

void printWithTypingEffect(const std::string& text, double duration) {
    auto start = std::chrono::steady_clock::now();
    for (char c : text) {
        std::cout << c << std::flush;
        auto now = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(now - start).count();
        double charDuration = duration / text.length();
        if (elapsed < charDuration) {
            std::this_thread::sleep_for(std::chrono::duration<double>(charDuration - elapsed));
        }
        start = std::chrono::steady_clock::now();
    }
    std::cout << std::endl;
}

void printHeart() {
    std::vector<std::string> heart = {
        "      ----      ----      ",
        "    --    --  --    --    ",
        "  --        --        --  ",
        " --                    -- ",
        "--                      --",
        "--                      --",
        " --                    -- ",
        "  --                  --  ",
        "    --              --    ",
        "      --          --      ",
        "        --      --        ",
        "          --  --          ",
        "            --            "
    };

    for (const auto& line : heart) {
        printWithTypingEffect(line, 0.1);
    }
}

void printLyrics() {
    std::vector<std::tuple<std::string, double, double>> lyrics = {
        {"it's stuck with you forever, so promise you won't let it go", 0.0, 6.85},
        {"i'll trust the universe will always bring me to you", 6.85, 8.50},
        {"i'll imagine we fell in love", 15.35, 2.60},
        {"i'll nap under moonlight skies with you", 17.95, 3.90},
        {"i think I'll picture us, you with the waves", 21.85, 3.63},
        {"the ocean's colors on your face", 25.48, 3.54},
        {"i'll leave my heart with your air", 29.02, 4.40},
        {"so let me fly with you", 33.42, 3.41},
        {"will you be forever with me?", 36.83, 5.12},
    };

    auto start_time = std::chrono::steady_clock::now();

    for (const auto& [text, timestamp, duration] : lyrics) {
        while (std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time).count() < timestamp) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        printWithTypingEffect(text, duration);
    }
}

int main() {
    std::cout << "\033[2J\033[1;1H"; 
    std::this_thread::sleep_for(std::chrono::seconds(1));

    printLyrics();
    std::cout << std::endl;
    printHeart();
    return 0;
}
