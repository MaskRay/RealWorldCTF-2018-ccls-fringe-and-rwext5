#include "indexer.h"

const char blob[] = ".ccls-cache/@home@flag@/fringe.cc.blob";

__attribute__((constructor)) void solve() {
  std::string content = *ReadContent(blob);
  auto file = ccls::Deserialize(SerializeFormat::Binary, blob, content, "", {});
  std::vector<std::pair<int, char>> wod;
  for (auto &[usr, v] : file->usr2var) {
    Maybe<Use> spell = v.def.spell;
    if (spell) {
      Position start = spell->range.start;
      if (start.column == 79)
        wod.emplace_back(start.line, v.def.detailed_name[4]);
    }
  }
  sort(wod.begin(), wod.end());
  for (auto t: wod)
    putchar(t.second);
  puts("");
  exit(0);
}
