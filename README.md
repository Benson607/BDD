# 程式介紹
此程式可將pla檔案轉換成dot檔案，但僅能處理單個output

目前可處理之pla指令:

    .i
    .o
    .p
    .ilb
    .ob
    .e

# 所需函式庫

    iostream
    fstream
    sstream
    string
    vector
    set

# 使用方式
進入main.cpp所在之資料夾，並以g++進行編譯

    g++ main.cpp -o main

若無法正常編譯，請確認您是否安裝g++，且能正常連結到所需之函式庫，或是手動連結所需函式庫

或是使用資料夾內提供的setup.sh

使用下面指令將pla轉換成dot

    ./main [pla來源] [目標dot檔案]

若目標dot檔案不存在，則會創造該檔案

示範

    g++ main.cpp -o main
    ./main src.pla trg.dot