#ifndef HIT_AND_BLOW_INCLUDE
#define HIT_AND_BLOW_INCLUDE

#include <string>  // for string
#include <utility> // for move
#include <cstddef> // for size_t

// 一度のユーザー入力の結果
struct Result {
    std::size_t hitCount = 0;
    std::size_t blowCount = 0;
};

// ユーザー入力の検証結果
// 不正な場合は、isValid == falseとなり、
// errorReasonに理由の文言が代入される。
struct ValidationResult {
    bool isValid = false;
    std::string errorReason;

    ValidationResult(bool isValid, std::string&& errorReason)
        : isValid(isValid), errorReason(std::move(errorReason)) {}
};

class HitAndBlow {
    std::string answer_; // コンピュータが考えた数字
public:
    // コンピュータが、4桁の数字を考える
    // 考える数字は、[0, 9]の数字を重複なく4個。
    void thinkComputer();

    // デバッグ用に、答えを取得する。
    //
    // 設計論拠：
    // 積極的に使ってほしくない関数は、使いにくくする。
    // ここでは、関数名を長くすることで、使いにくくしている。
    std::string getAnswerForDebug() const
    {
        return answer_;
    }

    // ルール説明の文言を取得する。
    std::string getRule() const;

    // ユーザーの入力を検証する。
    ValidationResult isValid(const std::string& userValue) const;

    // ユーザーの回答を入力し、結果を取得する。
    Result askUser(const std::string& userValue) const;

    // ゲームクリアかどうかを判定する
    bool isClear(const Result& result) const
    {
        return result.hitCount == getMaxDigit() && result.blowCount == 0;
    }

    // 入力する桁数を取得する
    std::size_t getMaxDigit() const
    {
        return 4;
    }
};

#endif // HIT_AND_BLOW_INCLUDE

