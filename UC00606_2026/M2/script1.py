# Solicita a pontuação CVSS ao utilizador
cvss = float(input("Introduza a pontuação CVSS (0.0 a 10.0): "))

# Validação Zero Trust
if cvss < 0.0 or cvss > 10.0:
    print("Erro: Valor inválido.")
else:
    # Estrutura if/elif/else que determina a severidade
    if cvss <= 3.9:
        print("Severidade: Baixa")
    elif cvss <= 6.9:
        print("Severidade: Média")
    elif cvss <= 8.9:
        print("Severidade: Alta")
    else:
        print("Severidade: Crítica")