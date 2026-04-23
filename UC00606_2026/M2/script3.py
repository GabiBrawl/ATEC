porta = int(input("Introduza a porta de rede: "))

# Validação primária 
if porta < 0 or porta > 65535:
    print("Erro: Porta fora do limite arquitetural.")
else:
    # Estrutura match-case
    match porta:
        case 22:
            print("Porta Crítico: SSH")
        case 80:
            print("Porta Crítico: HTTP")
        case 443:
            print("Porta Crítico: HTTPS")
        case 3389:
            print("Porta Crítico: RDP")
        case _: # default case
            print("Porta Não Monitorizada")