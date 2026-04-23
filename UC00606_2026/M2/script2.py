tipo_conta = input("Tipo de conta (admin/user): ")
idade_pass = int(input("Idade da password em dias: "))

# Validação Zero Trust estrita
if tipo_conta != "admin" and tipo_conta != "user":
    print("ALERTA: Tentativa de manipulação detectada!")
else:
    # Lógica de negócio com operadores lógicos
    if (tipo_conta == "admin" and idade_pass > 30) or (tipo_conta == "user" and idade_pass > 90):
        print("Exige Alteração Imediata")
    else:
        print("Password Válida")