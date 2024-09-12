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
進入main.cpp所在之資料夾，請執行下面指令進行編譯

    g++ main.cpp -o [輸出名稱]

若無法正常編譯，請確認g++是否能正常連結到所需之函式庫，或是手動連結所需函式庫

使用下面指令將pla轉換成dot

    ./[輸出名稱] [pla來源] [目標dot檔案]

若目標dot檔案不存在，則會創造該檔案

示範

    g++ main.cpp -o main
    ./main src.pla trg.dot