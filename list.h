/* Jingxin Zhang */

int deleteSome(void *p2head, CriteriaFunction mustGo, ActionFunction disposal, int text);
int insert(void *p2head, void *data, ComparisonFunction order, int text);
void iterate(void *p2head, ActionFunction doThis);
void sort(void *p2head, ComparisonFunction cf);
