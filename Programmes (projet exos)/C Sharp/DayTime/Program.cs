using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DayTime
{
    class Program
    {
        static void Main(string[] args)
        {
            if (DateTime.Now.DayOfWeek == DayOfWeek.Saturday ||
            DateTime.Now.DayOfWeek == DayOfWeek.Sunday ||
            (DateTime.Now.DayOfWeek == DayOfWeek.Monday && DateTime.Now.Hour < 9) ||
            (DateTime.Now.DayOfWeek == DayOfWeek.Friday && DateTime.Now.Hour >= 18))
            {
                // nous sommes le week-end
                AfficherBonWeekEnd();
            }
            else
            {
                // nous sommes en semaine
                if (DateTime.Now.Hour >= 9 && DateTime.Now.Hour < 18)
                {
                    // nous sommes dans la journée
                    AfficherBonjour();
                }
                else
                {
                    AfficherBonsoir();
                }
            }
        }
        static void AfficherBonWeekEnd()
        {
            Console.WriteLine("Bon week-end " + Environment.UserName);
            Console.ReadKey();
        }

        static void AfficherBonjour()
        {
            Console.WriteLine("Bonjour " + Environment.UserName);
            Console.ReadKey();
        }

        static void AfficherBonsoir()
        {
            Console.WriteLine("Bonsoir " + Environment.UserName);
            Console.ReadKey();
        }
    }
}