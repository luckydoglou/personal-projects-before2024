# Xiaolou Huang (Lor)
# WiCS-Programming-Competition, 2017
# Problem 1

def chandelierShopping(layers):
    # variables
    PRICE_OF_EACH_CRYSTAL = 100
    crystals = 0
    symbolAlter = True  # for alternating the symbol '!' and '-'
    
    for i in range(layers + 1):
        crystals += i
    price = crystals * PRICE_OF_EACH_CRYSTAL
     
    # formating output
    print(f'Price: ${price}')
    for i in range(1, layers + 1):  #from top layer to bottom layer
        print("$", end="")
        
        # alternating the symbols
        if symbolAlter == True:
            for j in range(i, layers):
                print("!$", end="")
            print()
            symbolAlter = False
        else:
            for k in range(i, layers):
                print("-$", end="")
            print()
            symbolAlter = True
            
def main():
    layers = int(input("How many layers do you want: "))
    chandelierShopping(layers)

main()


