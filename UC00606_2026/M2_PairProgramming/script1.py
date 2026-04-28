PORT_HTTP = "80"
PORT_HTTPS = "443"
PORT_SSH = "22"

SEPARATOR = ","
 
while True:  # loop principal: repete até obter uma entrada válida
    user_input = input('Introduza a string de portas (separadas por "' + SEPARATOR + '"): ')  # lê a string do utilizador
    if not user_input:  # validação: não pode ser vazia
        print("Entrada vazia. Tente novamente...")
        continue
    if " " in user_input:  # validação: proíbe espaços
        print("Não use espaços. Ex: 80,443,22")  # explica formato aceito
        continue
    allowed = set("0123456789" + SEPARATOR)  # caracteres permitidos: dígitos e vírgula
    invalid_char = False  # flag para detectar caracteres inválidos
    for ch in user_input:  # percorre cada carácter da string
        if ch not in allowed:  # se encontrar algo que não é dígito nem vírgula
            invalid_char = True  # marca como inválido
            break  # sai do ciclo cedo
    if invalid_char:  # se existem caracteres inválidos
        print("Caracteres inválidos. Use apenas dígitos e vírgulas.")
        continue
    if user_input.startswith(SEPARATOR) or user_input.endswith(SEPARATOR) or SEPARATOR * 2 in user_input:  # validação formato de separadores
        print("Formato inválido de separadores.")  # vírgula inicial/final ou dupla é inválida
        continue
    parts = user_input.split(SEPARATOR)  # divide a string em tokens (cada token é uma porta em string)
    ports = []  # lista onde serão guardadas as portas convertidas para int
    ok = True  # flag geral para saber se todas as portas são válidas
    for p in parts:  # percorre cada token
        try:
            port = int(p)  # tenta converter token para inteiro
        except ValueError:  # falha se token não for número (proteção extra)
            ok = False  # marca entrada como inválida
            break  # sai do ciclo
        if not (0 < port <= 65535):  # validação intervalo de portas válido
            ok = False  # porta fora do intervalo permitido
            break
        ports.append(port)  # adiciona porta válida à lista
    if not ok:  # se alguma conversão/validaçãoção falhou
        print("Porta inválida; cada porta deve estar entre 1 e 65535.")  # avisa o utilizador
        continue  # repete o pedido
    break  # todas as verificações passaram: sai do loop

print(ports)  # imprime a lista de portas válidas (inteiros)



