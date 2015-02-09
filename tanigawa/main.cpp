#include <iostream>

// 桁数決定
const int RIMITNUM = 4;

bool numchk(int* randnum, int ransu,int i){

    for(int n=0; n<i; ++n){
        if(randnum[n] == ransu){
            return false;        
        }
    }
    return true;
}

void getransu(int* randnum){
    
    int ransu;

    srand(time(0));

    // 乱数を４桁取得する。重複していないこと
    for(int i=0; i<RIMITNUM;){
        int ransu = 1 + rand() % 9;
        if(!numchk(randnum,ransu,i)){
	    // 重複あり。乱数取り直し
            continue;        
        }
        randnum[i] = ransu;
        ++i;
    }
}

int hitchk(int* randnum, int* trynum){
    int hitflg=0;

    for (int i=0; i<RIMITNUM; ++i) {
        if(randnum[i] == trynum[i]){
            ++hitflg;
        }
    }
    std::cout << "hit:";
    std::cout << hitflg << std::endl;
    return hitflg;
}

void blowchk( int* randnum, int* trynum, int hitflg){
    int blowflg=0;

    for(int i=0; i<RIMITNUM; ++i){
        for(int n=0; n<RIMITNUM; ++n){
            if(randnum[i] == trynum[n]){
                ++blowflg;
            }
            ++i;
        }
    }
    std::cout << "blow:";
    std::cout << blowflg - hitflg << std::endl;
}

int main()
{
    int randnum[RIMITNUM];
    int trynum[RIMITNUM];
    int exitflg=0;
    getransu(randnum);

    // コンピュータが選ぶ数は０−９
    // 数字の重複はhitのチェックができないため不可

    for (int x : randnum) {
        std::cout << x;
    }
    std::cout << std::endl;

   // 入力格納
    while(exitflg != RIMITNUM){    
        // 入力を促す表示
        std::cout << "数字を" << RIMITNUM << "回入力してください" << std::endl;
        for(int i=0; i<RIMITNUM; ++i){
            std::cin >> trynum[i];    
        }
        for (int x : trynum) {
            std::cout << x;
        }
        std::cout << std::endl;
        exitflg = hitchk(randnum,trynum);

        // blow?
        blowchk(randnum,trynum,exitflg);
        if(exitflg == RIMITNUM){
            std::cout << "COMPLETE！" << std::endl;
        }
    }
}

