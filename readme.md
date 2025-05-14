Kazys Tatarunas - RM564020
Eduardo Viudes - RM564075
Victor Tadashi - RM563582
Lucas Marson - RM563975
Frederico de Paulo - RM562109

Este código implementa um sistema de monitoramento ambiental para a Vinheria Agnello, utilizando sensores simulados de luminosidade (LDR), temperatura e umidade, todos conectados a entradas analógicas de um Arduino.

Ele lê os valores dos sensores e calcula médias móveis para suavizar as medições. Com base nessas médias:

Controla LEDs (verde, amarelo e vermelho) para indicar as condições de luminosidade, temperatura e umidade.

Ativa um buzzer em caso de condições fora dos padrões ideais.

Exibe mensagens em um display LCD rotativamente a cada 5 segundos, informando o estado de cada variável (luminosidade, temperatura ou umidade).

Também imprime os dados no monitor serial para visualização no computador.

O código está organizado em funções separadas para cada tipo de verificação (luminosidade, temperatura e umidade), melhorando a clareza e a manutenção do programa.