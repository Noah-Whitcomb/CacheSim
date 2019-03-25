echo off
cd C:\Users\crisc\CLionProjects\CacheSimulator\CacheSim\cmake-build-debug

break>C:\python_scripts\graph1data.txt
break>C:\python_scripts\graph2data.txt
break>C:\python_scripts\graph3data.txt

rem this is for graph 1 
CacheSimulator.exe -s 1024 -b 32 -a 4 >> C:\python_scripts\graph1data.txt
CacheSimulator.exe -s 2048 -b 32 -a 4 >> C:\python_scripts\graph1data.txt
CacheSimulator.exe -s 4096 -b 32 -a 4 >> C:\python_scripts\graph1data.txt
CacheSimulator.exe -s 8192 -b 32 -a 4 >> C:\python_scripts\graph1data.txt
CacheSimulator.exe -s 16384 -b 32 -a 4 >> C:\python_scripts\graph1data.txt
CacheSimulator.exe -s 32768 -b 32 -a 4 >> C:\python_scripts\graph1data.txt
CacheSimulator.exe -s 65536 -b 32 -a 4 >> C:\python_scripts\graph1data.txt

rem this is for graph 2
CacheSimulator.exe -s 8192 -b 1 -a 4 >> C:\python_scripts\graph2data.txt
CacheSimulator.exe -s 8192 -b 2 -a 4 >> C:\python_scripts\graph2data.txt
CacheSimulator.exe -s 8192 -b 4 -a 4 >> C:\python_scripts\graph2data.txt
CacheSimulator.exe -s 8192 -b 8 -a 4 >> C:\python_scripts\graph2data.txt
CacheSimulator.exe -s 8192 -b 16 -a 4 >> C:\python_scripts\graph2data.txt
CacheSimulator.exe -s 8192 -b 32 -a 4 >> C:\python_scripts\graph2data.txt
CacheSimulator.exe -s 8192 -b 64 -a 4 >> C:\python_scripts\graph2data.txt

rem this is for graph 3
CacheSimulator.exe -s 8192 -b 32 -a 1 >> C:\python_scripts\graph3data.txt
CacheSimulator.exe -s 8192 -b 32 -a 2 >> C:\python_scripts\graph3data.txt
CacheSimulator.exe -s 8192 -b 32 -a 4 >> C:\python_scripts\graph3data.txt
CacheSimulator.exe -s 8192 -b 32 -a 8 >> C:\python_scripts\graph3data.txt
CacheSimulator.exe -s 8192 -b 32 -a 16 >> C:\python_scripts\graph3data.txt
CacheSimulator.exe -s 8192 -b 32 -a 32 >> C:\python_scripts\graph3data.txt
CacheSimulator.exe -s 8192 -b 32 -a 256 >> C:\python_scripts\graph3data.txt

cd C:\python_scripts\

py .\make_cachegraphs.py