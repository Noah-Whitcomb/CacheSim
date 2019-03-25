import re
import matplotlib.pyplot as plt

x = []
y = []

def get_data(pathtofile, whichval, x, y):
    x.clear()
    y.clear()
    with open(pathtofile,'r') as data:
        s = data.read()
        s = s.splitlines()
        for i in range(len(s)-5):
            if whichval == 'a':
                assoc = re.search(r'associativity: \d+',s[i])
                missrate = re.search(r'miss rate: \d\.\d+',s[i+5])
                if assoc is not None and missrate is not None:
                    assoc = re.sub(r'associativity: ','',assoc.group())
                    missrate = re.sub(r'miss rate: ','',missrate.group())
                    x.append(assoc)
                    y.append(missrate)
            if whichval == 's':
                if(i < len(s)-7):
                    size = re.search(r'cache size: \d+',s[i])
                    missrate = re.search(r'miss rate: \d\.\d+',s[i+7])
                    if size is not None and missrate is not None:
                        size = re.sub(r'cache size: ','',size.group())
                        missrate = re.sub(r'miss rate: ','',missrate.group())
                        x.append(size)
                        y.append(missrate)
            if whichval == 'b':
                if(i < len(s)-6):
                    blocksize = re.search(r'block size: \d+',s[i])
                    missrate = re.search(r'miss rate: \d\.\d+',s[i+6])
                    if blocksize is not None and missrate is not None:
                        blocksize = re.sub(r'block size: ','',blocksize.group())
                        missrate = re.sub(r'miss rate: ','',missrate.group())
                        x.append(blocksize)
                        y.append(missrate)
        for i in range(len(x)):
            x[i] = int(x[i])
            y[i] = float(y[i])

def make_graph(xaxis, yaxis, nameofgraph, xlabel, units, index):
    x = xaxis 
    y = yaxis
    plt.figure(index)
    # plotting the points  
    plt.plot(x, y, color='green', linestyle='dashed', linewidth = 3, 
         marker='o', markerfacecolor='blue', markersize=12) 
    plt.scatter(x,y)
    
    # naming the x axis 
    if units != '':
        plt.xlabel('{} (in {})'.format(xlabel, units))
    else:
        plt.xlabel(xlabel) 
    # naming the y axis 
    plt.ylabel('miss rate') 
    
    # giving a title to my graph 
    plt.title(nameofgraph) 
     
    #plt.show()
    plt.savefig(xlabel)

get_data('graph1data.txt','s', x, y)
make_graph(x, y, 'size vs miss rate', 'size', 'bytes', 1)
get_data('graph2data.txt','b', x, y)
make_graph(x, y, 'block size vs miss rate', 'block size', 'bytes', 2)
get_data('graph3data.txt', 'a', x, y)
make_graph(x, y, 'associativity vs miss rate', 'associativity', '', 3)

