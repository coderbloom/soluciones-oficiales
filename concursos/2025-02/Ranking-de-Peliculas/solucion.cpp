#include <iostream>
#include <map>
#include <string>

using namespace std;

constexpr int maxn = 1e5 + 5;
int p[maxn];
map<string, pair<int, int>> name_to_id;
map<int, string> id_to_name;
int cnt = 1;

void Init() {
  for (int i = 0; i < maxn; ++i) {
    p[i] = i;
  }
}

int Find(int x) {
  if (x == p[x]) {
    return x;
  }
  return p[x] = Find(p[x]);
}

void Union(const string& x, const string& y) {
  const int id_x = name_to_id[x].first;
  const int id_y = name_to_id[y].first;
  const int root_x = Find(id_x);
  const int root_y = Find(id_y);

  const string& root_x_name = id_to_name[root_x];
  const string& root_y_name = id_to_name[root_y];
  const int rating_x = name_to_id[root_x_name].second;
  const int rating_y = name_to_id[root_y_name].second;
  // Al realizar la union de dos conjuntos, primero tenemos
  // en cuenta el rating de las peliculas, y como segundo
  // criterio sus nombres. De esta manera la pelicula que
  // buscamos en cada query siempre estara en la raiz del
  // conjunto.
  if (rating_x == rating_y) {
    // x es menor lexicograficamente que y
    if (root_x_name.compare(root_y_name) < 0) {
      p[root_y] = root_x;
    } else {
      p[root_x] = root_y;
    }
  } else if (rating_x < rating_y) {
    p[root_x] = root_y;
  } else {
    p[root_y] = root_x;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  Init();
  string name1, name2;
  int n, m, q, ri;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> name1 >> ri;
    name_to_id[name1] = {cnt, ri};
    id_to_name[cnt++] = name1;
  }
  cin >> m;
  while (m--) {
    cin >> name1 >> name2;
    Union(name1, name2);
  }
  cin >> q;
  while (q--) {
    cin >> name1;
    const int id_v = name_to_id[name1].first;
    const int root_v = Find(id_v);

    if (id_v == root_v) {
      cout << "Sin resultados\n";
    } else {
      cout << id_to_name[root_v] << '\n';
    }
  }

  return 0;
}
