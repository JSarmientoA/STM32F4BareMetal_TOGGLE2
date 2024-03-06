#include <stdint.h>

#define PERIPH_BASE					(0x40000000UL)//UL = Unsigned Long.Donde 0x40000000 es la dirección de memoria donde
                                      //inician todos los periféricos
#define AHB1PERIPH_OFFSET			(0x00020000UL)//Desplazamiento hacia la posicision de memoria donde esta ubicado
												//el bus AHB1(Advanced High Performance) (Bus Avanzado de alto Rendimiento)
#define AHB1PERIPH_BASE				(PERIPH_BASE + AHB1PERIPH_OFFSET)// Esto es 0x40000000UL + 0x00020000UL = 0x40020000UL.
																	// Primera posicion de memoria donde se ubica el bus AHB1
#define GPIOA_OFFSET				(0x0000)//Desplazamiento hacia la posicion de memoria que conecta el bus AHB1 con
											//el periferico GPIOA
#define GPIOA_BASE					(AHB1PERIPH_BASE + GPIOA_OFFSET)//Posicion de memoria donde esta ubicado el bus AHB1 que
																//conecta al periférico GPIOA
#define RCC_OFFSET					(0x3800UL)//Desplazamiento hacia la posicion de memoria que conecta el bus AHB1 con
											//el periferico RCC
#define RCC_BASE					(AHB1PERIPH_BASE + RCC_OFFSET)//Posicion de memoria donde esta ubicado el bus AHB1 que
																//conecta al periférico RCC
#define AHB1EN_R_OFFSET				(0x30UL)//Desplazamiento en la posicion de memoria para llegar al periferico RCC
										//que configur sus registros

#define GPIOAEN						(1U<<0)//Donde 1U<<0 significa poner un uno en la posicion cero. bitU<<n.
											//Donde bit = estado del bit 1/0. << "poner en". n = posicion.
											//Habilitacion del del reoj para el puerto A
#define	MODER_R_OFFSET				(0x00UL)//Desplazamiento en la posicion de memoria pa llegar al periferico MODER

#define OD_R_OFFSET					(0x14UL)//Desplazamiento en la posicion de memoria para llegar al periferico ODR
										//que configur sus registros

#define PIN5						(1U<<5)//Poner un uno en la posicion 5
#define LED_PIN						PIN5
#define __IO 						volatile
/*
 * Nota se utiliiza el apuntador *(volatile unsigned int*) para que el compilador apunte ala
 * dirección de memoria especificada por el registro. Ejemplo RCC_AHB1EN_R=(*(volatile unsigned int*)(RCC_BASE + HB1EN_R_OFFSET)) apuenta a la
 * dirección de memoria correspondite añ registro RCC_AHB1EN_R.
*/

typedef struct
{
	__IO uint32_t DUMMY[12];//Esta matriz se utiliza para reemplazar los reguistros que no se van a utulizar.
	                   //El tamaño de la matriz es proporcional el numero de registros
	__IO uint32_t AHB1ENR; /*Registro de conexion del reloj con el periferico bus AHB1*/

}RCC_TypeDef;

typedef struct
{
	/*__IO = valatile*/
	__IO uint32_t MODER;	/*Puerto GPIO Regidtro modo del puerto 					dirección de offset 0x00*/
	__IO uint32_t OTYPER;	/*Puerto GPIO Rgitro tipo de salida						dirección de offset 0x04*/
	__IO uint32_t OSPEEDR;	/*Puerto GPIO Rgitro velocidad de salida				dirección de offset 0x08*/
	__IO uint32_t PUPDR;	/*Puerto GPIO Rgitro configuracion pull up-pull down	dirección de offset 0x0C*/
	__IO uint32_t IDR;		/*Puerto GPIO Rgitro configuracion como entrada			dirección de offset 0x10*/
	__IO uint32_t ODR;		/*Puerto GPIO Rgitro configuracion como salida			dirección de offset 0x14*/
	__IO uint32_t BSRR;		/*Puerto GPIO Rgitro bit set/reset						dirección de offset 0x18*/
	__IO uint32_t LCKR;		/*Puerto GPIO Rgitro configuracion de reloj				dirección de offset 0x1C*/
	__IO uint32_t AFR[2];	/*Puerto GPIO Rgitro de funciones alternativas			dirección de offset 0x20-0x24*/

}GPIO_TypeDef;

#define RCC		((RCC_TypeDef*)RCC_BASE)//Esto nos dice que RCC_BASE esta apuntando a la estructura RCC_TypeDef
#define GPIOA	((GPIO_TypeDef*)GPIOA_BASE)//Esto nos dice que GPIOA_BASE esta apuntando a la estructura GPIO_TypeDef

int main(void){
//PASOA
	//1. Habilitar el acceso a reloj al GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//2. Configurar el PIN 5 como salida
	GPIOA -> MODER |=  (1U<<10);//poner un uno en la posicion dies |= es or igual
	GPIOA -> MODER &=~ (1U<<11);//poner un cero en la posicion once &=~ es and igual negado
	while(1){
		//3. Setear el pin 5 en alto
		//GPIOA_OD_R |= LED_PIN;
		//4. Alternar
		GPIOA ->ODR ^= LED_PIN;// Donde ^= significa alternancia
		for(int i=0;i<1900000;i++){}
	}

}
