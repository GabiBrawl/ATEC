dados = float(input("Quantidade de dados exfiltrados (GB): "))

# Verificação de integridade dos dados
if dados < 0:
    print("Erro: Valor negativo não permitido.")
else:
    # Classificação de segurança
    if dados <= 5:
        pass # Sem alerta
    elif dados <= 50:
        print("Alerta Laranja: Possível extração em curso")
    else:
        print("Alerta Vermelho: Isolamento imediato da máquina!")