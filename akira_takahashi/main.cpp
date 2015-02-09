// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include "HitAndBlow.h"

int main()
{
    HitAndBlow game;
    game.thinkComputer();

    std::cout << game.getRule() << std::endl;
    std::cout << game.getAnswerForDebug() << std::endl;

    for (;;) {
        std::cout << "4桁の数字を入力してください：";

        std::string userValue;
        std::cin >> userValue;

        const ValidationResult validResult = game.isValid(userValue);
        if (!validResult.isValid) {
            std::cout << validResult.errorReason << std::endl;
            continue;
        }

        const Result result = game.askUser(userValue);
        if (game.isClear(result)) {
            std::cout << "おめでとうございます！ゲームクリアです！" << std::endl;
            break;
        }

        std::cout << "ヒット：" << result.hitCount << " "
                  << "ブロー：" << result.blowCount
                  << std::endl;
    }
}
