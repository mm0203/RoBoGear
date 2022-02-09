//=============================================================================
// singleton.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "singleton.h"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace 
{  
    // 最大インスタンス数を設定
    constexpr int k_MaxInstanceSize = 256;
    // 排他的制御用
    std::mutex g_Mutex;
    // インスタンス数カウント用変数
    int g_NumInstanceCnt = 0;
    // インスタンスを格納する配列
    SingletonFinalizer::FinalizerFunc g_Instances[k_MaxInstanceSize]; 
}

//=============================================================================
// 
// インスタンス数設定
// 
//=============================================================================
void SingletonFinalizer::addFinalizer(FinalizerFunc func)
{
    std::lock_guard<std::mutex> lock(g_Mutex);

    // 最大保有数を超えたら例外処理
    assert(g_NumInstanceCnt < k_MaxInstanceSize);

     // インスタンスを初期化
    g_Instances[g_NumInstanceCnt] = func;

    g_NumInstanceCnt++;
}

//=============================================================================
// 
// インスタンス破棄
// 
//=============================================================================
void SingletonFinalizer::finalize() 
{
    std::lock_guard<std::mutex> lock(g_Mutex);

    // インスタンスを1つずつ破棄していく
    for (int i = g_NumInstanceCnt - 1; i >= 0; --i) 
    {
        // インスタンス削除
        (*g_Instances[i])();     
        g_Instances[i] = nullptr;
    }
    // インスタンス数をリセット
    g_NumInstanceCnt = 0;
}