# vamos rodar o program N vezes e salvar o resultado que foi salvo em result.txt em um set,
# apenas para ver as diferentes respostas que o programa pode dar

import os
set_ans = set()
for i in range(2000):
    os.system("./program 30")
    with open("result.txt") as f:
        set_ans.add(f.read())
        
print(len(set_ans))
for ans in set_ans:
    print(ans.replace("\n", ""))