using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JusteValeur
{
    class Program
    {
        static void Main(string[] args)
        {
            int FindOut = new Random().Next(0, 100);
            int nombreDeCoups = 0;
            Console.WriteLine("Veuillez saisir un nombre compris entre 0 et 100 (exclu)");
            while (true)
            {
                string saisie = Console.ReadLine();
                int valeurSaisie;
                if (!int.TryParse(saisie, out valeurSaisie))
                {
                    Console.WriteLine("La valeur saisie est incorrecte, veuillez recommencer ...");
                    continue;
                }
                if (valeurSaisie < 0 || valeurSaisie >= 100)
                {
                    Console.WriteLine("Vous devez saisir un nombre entre 0 et 100 exclu ...");
                    continue;
                }
                nombreDeCoups++;
                if (valeurSaisie == FindOut)
                    break;
                if (valeurSaisie < FindOut)
                {
                    Console.WriteLine("Trop petit ...");
                }
                else
                    Console.WriteLine("Trop grand ...");
            }
            if (nombreDeCoups == 1)
            {
                Console.WriteLine("Vous avez trouvé en " + nombreDeCoups + " coup");
            }
            else { 
                Console.WriteLine("Vous avez trouvé en " + nombreDeCoups + " coups");
            }
         Console.ReadKey(true);
        }
        
    }
}