//=============================================================================
// singleton.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <cassert>
#include <mutex>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
// インスタンス破棄クラス
class CSingletonFinalizer
{
public:
    // デリート用汎用ポインタ
    using FinalizerFunc = void(*)();
    // インスタンス数カウント用
    static void addFinalizer(FinalizerFunc func); 
    // インスタンス破棄
    static void finalize();
};

// シングルトンクラス
template <typename T>

class CSingleton
{
public:
    //オブジェクトのインスタンスはここににしか存在しない
    static T& GetInstance()
    {
        // インスタンス生成は１度だけ
        if (!Instance)  Create();
        return *Instance;
    }

private:
    // インスタンス生成
    static void Create()
    {
        Instance = new T;

        // インスタンス数をカウント
        CSingletonFinalizer::addFinalizer(&CSingleton<T>::Destroy);
    }

    // インスタンス削除
    static void Destroy() 
    {
        delete Instance;
        Instance = nullptr;
    }

private:
    static T* Instance;

protected:
    // コンストラクタの使用を外部から禁止する
    CSingleton() = default;
    CSingleton(const CSingleton&) = delete;
    CSingleton& operator=(const CSingleton&) = delete;
    CSingleton(CSingleton&&) = delete;
    CSingleton& operator=(CSingleton&&) = delete;
};

// 静的メンバ
template <typename T> T* CSingleton<T>::Instance = nullptr;