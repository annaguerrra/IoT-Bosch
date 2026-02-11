import pyads


# criando um objeto de conexão com PLC

# AMS Net ID -> id de qual PLC eu quero acessar
malo = "10.234.198.62.1.1"
ipMalo = "10.234.199.183"

# ip de quem está enviando
anna = "10.234.195.79.1.1"

# porta do serviço do PLC -> canal de comunicação
porta = pyads.PORT_TC3PLC1
plc = pyads.Connection(malo, porta, ipMalo)

# iterando na váriavel 
plc.open()
# y = plc.read_by_name("GVL.x")

plc.write_by_name("GVL.tempo", 2)

plc.close()


