tentativas_falhas = int(input("Número de tentativas de autenticação falhadas: "))

# Validação primária
if tentativas_falhas < 0:
    print("Erro: Valor negativo não permitido.")
else:
    # Classificação de risco de brute force
    if tentativas_falhas == 0:
        print("Status: Seguro")
    elif tentativas_falhas <= 3:
        print("Alerta Amarelo: Atividade suspeita detectada")
    elif tentativas_falhas <= 10:
        print("Alerta Laranja: Possível ataque brute force")
    else:
        print("Alerta Vermelho: Bloqueio imediato da conta!")
