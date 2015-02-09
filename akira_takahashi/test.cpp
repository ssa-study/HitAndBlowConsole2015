// Hit and Blowが正しく動作するか確認するためのテストコード

#include "HitAndBlow.h"
#include <boost/detail/lightweight_test.hpp>

HitAndBlow makeGame()
{
    HitAndBlow game;
    game.thinkComputer();
    return game;
}

// 回答が4桁あるか確認する
void testIsValidAnswer()
{
    HitAndBlow game = makeGame();
    BOOST_TEST(game.getAnswerForDebug().size() == game.getMaxDigit());
}

// 不正なユーザー入力が、正しく不正と判断されるか確認する
void testValidUserAsk()
{
    HitAndBlow game = makeGame();

    // 桁数の過不足
    BOOST_TEST(!game.isValid("123").isValid);
    BOOST_TEST(!game.isValid("12345").isValid);

    // 数字以外が入力された
    BOOST_TEST(!game.isValid("123a").isValid);

    // 数字が4桁：正しい
    BOOST_TEST(game.isValid("1234").isValid);
}

void testClear()
{
    HitAndBlow game = makeGame();

    // 正しい回答を入力することで、ゲームクリアとなること
    const Result result = game.askUser(game.getAnswerForDebug());
    BOOST_TEST(game.isClear(result));

    // 間違った回答を作って入力することｄ，ゲームクリアとならないこと
    const std::string answer = game.getAnswerForDebug();
    const std::string badAnswer = answer.substr(0, answer.size() - 1) +
                                    (answer.back() == '0' ? '1' : '0');
    const Result badResult = game.askUser(badAnswer);
    BOOST_TEST(!game.isClear(badResult));
}

int main()
{
    // ランダムな回答を1000回作って、テストを施行
    for (int i = 0; i < 1000; ++i) {
        testIsValidAnswer();
        testValidUserAsk();
        testClear();
    }

    return boost::report_errors();
}
