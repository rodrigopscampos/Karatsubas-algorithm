using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

//
//
//


namespace SCC
{
    public class Program
    {
        public struct Vertex
        {
            public int N;
            public List<int> Edges;

            public Vertex(int n, IEnumerable<int> edges)
            {
                N = n;
                Edges = edges.ToList();
            }

            public Vertex(int n)
            {
                N = n;
                Edges = new List<int>();
            }

            public override string ToString()
            {
                return string.Join(", ", Edges);
            }
        };

        static int T = 0;
        static int S;
        static int[] F;
        static Dictionary<int, int> leader = new Dictionary<int, int>();
        static bool[] explored;

        static void DFS_Recur(Dictionary<int, Vertex> g, int i)
        {
            explored[i] = true;
            leader[i] = S;

            if (!g.ContainsKey(i))
            {
                g.Add(i, new Vertex(i));
            }

            foreach (var j in g[i].Edges)
            {
                if (!explored[j])
                {
                    //Task.Run(() => DFS_Recur(g, j)).Wait();
                    DFS_Recur(g, j);
                }
            }

            T++;
            F[i] = T;
        }

        //Depth First Search Loop
        static void DFS_Loop(Dictionary<int, Vertex> g, int n)
        {
            Console.WriteLine("DFS Loop started \n");

            T = 0;
            explored = new bool[n + 1];
            F = new int[n + 1];

            leader.Clear();

            for (int i = n; i >= 1; i--)
            {
                if (!g.ContainsKey(i))
                {
                    g.Add(i, new Vertex(i));
                }

                if (!explored[i])
                {
                    S = i;
                    DFS_Recur(g, i);
                }

            }

            Console.Write("DFS Loop finished \n");
        }

        static Dictionary<int, Vertex> reverse_arcs(Dictionary<int, Vertex> g)
        {
            Console.Write("reverse started\n");

            var r = new Dictionary<int, Vertex>();
            foreach (var it in g)
            {
                foreach (var it2 in it.Value.Edges)
                {
                    if (!r.ContainsKey(it2))
                        r[it2] = new Vertex(it2, new List<int>());

                    r[it2].Edges.Add(it.Key);
                }
            }

            Console.Write("reverse finished\n");
            return r;
        }

        static Dictionary<int, Vertex> applyF(Dictionary<int, Vertex> g)
        {
            Console.Write("apply F started \n");

            var r = new Dictionary<int, Vertex>();
            foreach (var it in g)
            {
                r[F[it.Key]] = new Vertex(F[it.Key], new List<int>());

                foreach (var it2 in it.Value.Edges)
                {
                    r[F[it.Key]].Edges.Add(F[it2]);
                }
            }

            Console.Write("apply F finished \n");
            return r;
        }

        static List<KeyValuePair<int, int>> getSccSizes(int qty)
        {

            Console.Write("getSccSize started \n");

            var ret = new Dictionary<int, int>();
            foreach (var it in leader)
            {

                if (!ret.ContainsKey(it.Value))
                    ret[it.Value] = 0;

                ret[it.Value]++;
            }

            return ret
                .OrderByDescending(kvp => kvp.Value)
                .Take(qty)
                .ToList();
        }

        //Computing Strong Components
        static void Kosaraju(Dictionary<int, Vertex> g, int n)
        {
            Console.Write("Kosaraju started\n");

            var gRev = reverse_arcs(g);

            DFS_Loop(gRev, n);

            g = applyF(g);

            DFS_Loop(g, n);

            var l = getSccSizes(5);

            foreach (var it in l)
            {
                Console.Write(it.Key + ":" + it.Value + "\n");
            }

            Console.Write("----------\n");

            foreach (var it in l)
            {
                Console.Write(it.Value + ",");
            }
        }

        static void gAdd(Dictionary<int, Vertex> g, HashSet<int> nodes, int head, int tail)
        {
            if (!g.ContainsKey(head))
                g.Add(head, new Vertex(head, new List<int>()));

            g[head].Edges.Add(tail);
            nodes.Add(head);
            nodes.Add(tail);
        }

        static void gInit(Dictionary<int, Vertex> g, int begin, int end)
        {
            Console.Write("starting map\n");
            for (int i = begin; i <= end; i++)
            {
                g.Add(i, new Vertex(i, new List<int>()));
            }

            Console.Write("map finished\n");
        }

        static int Main()
        {
            Dictionary<int, Vertex> g = new Dictionary<int, Vertex>();
            HashSet<int> nodes = new HashSet<int>();
            Console.Write("read file started\n");

            //Sample1.txt Answer: 3,3,3,0,0
            //Sample2.txt Answer: 3,3,2,0,0
            //Sample3.txt Answer: 3,3,1,1,0
            //Sample4.txt Answer: 7,1,0,0,0
            //Sample5.txt Answer: 6,3,2,1,0;
            //SCC.txt     Answer: 434821,968,459,313,211

            int h, t;
            var ifstream = new StreamReader(File.Open("C:/temp/Sample1.txt", FileMode.Open));

            while (!ifstream.EndOfStream)
            {
                var line = ifstream.ReadLine().Split(' ');
                h = int.Parse(line[0]);
                t = int.Parse(line[1]);
                gAdd(g, nodes, h, t);
            }

            Console.Write("read file finished\n");

            Kosaraju(g, nodes.Count);

            Console.Write("fim\n");
            Console.ReadLine();
            return 0;
        }
    }
}
