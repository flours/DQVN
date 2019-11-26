import os
files = os.listdir('.')

for file in files:
    print(file[-4:])
    if file[-4:]!='.csv':continue
    f=open(file)
    str=f.read()
    str2=str[str.find('\n'):]
    f.close()
    f=open(file,mode='w')
    f.write(str2)
    f.close()

    