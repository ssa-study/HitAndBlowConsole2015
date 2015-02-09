#include <cassert>
#include <random>    // for random_device, mt19937
#include <algorithm> // for shuffle()
#include <string>    // for string
#include <cstddef>   // for size_t
#include "HitAndBlow.h"

// 入力候補となる文字の集合を受け取り、
// その文字が重複しないようsize個分の文字集合を作る。
std::string generateSequence(std::string candidates, std::size_t size)
{
    // 乱数のシードを作る
    // ハードウェア乱数を使用し、予測不能なシードにする
    std::random_device seedGenerator;
    const std::uint32_t seed = seedGenerator();

    // シードを使って、乱数生成器を初期化
    // 乱数生成器には、32ビット版のメルセンヌ・ツイスターを使用する。
    std::mt19937 randomEngine(seed);

    // 候補の文字列を、ランダムに並び替える
    std::shuffle(candidates.begin(), candidates.end(), randomEngine);

    // 先頭size個の要素を、コンピュータが考えた数値とする
    return candidates.substr(0, size);
}

void HitAndBlow::thinkComputer()
{
    const std::string candidates = "0123456789";
    answer_ = generateSequence(candidates, getMaxDigit());
}

std::string HitAndBlow::getRule() const
{
    return
        "====================ルール説明=====================\n"
        "| コンピュータが考えた、4つの数字を当ててください |\n"
        "| 位置と数字が合っていればヒット1、               |\n"
        "| 数字だけ合っていればブロー1です。               |\n"
        "| ヒット4になったらゲームクリアです！             |\n"
        "===================================================\n"
        "\n";
}

ValidationResult HitAndBlow::isValid(const std::string& userValue) const
{
    if (userValue.size() != getMaxDigit()) {
        return ValidationResult(false, "4桁の数字を入力してください");
    }

    if (std::any_of(userValue.begin(), userValue.end(), [](char c) {
            return std::isdigit(static_cast<int>(c)) == 0;
        })) {
        return ValidationResult(false, "全て数字で入力してください");
    }
    return ValidationResult(true, "");
}

Result HitAndBlow::askUser(const std::string& userValue) const
{
    // この関数を呼ぶために満たすべき事前条件。
    // assertマクロは、デバッグ時のみ動作し、式がfalseの場合はプログラムが異常終了する。
    // リリース時には動作しないので、開発中に取り除くべきロジックのエラーを検出するために使用する。
    assert(!answer_.empty());

    Result result;
    for (std::size_t i = 0; i < answer_.size(); ++i) {
        if (answer_[i] == userValue[i]) {
            ++result.hitCount;
        }
        else if (std::find(userValue.begin(), userValue.end(), answer_[i]) != userValue.end()) {
            ++result.blowCount;
        }
    }
    return result;
}

