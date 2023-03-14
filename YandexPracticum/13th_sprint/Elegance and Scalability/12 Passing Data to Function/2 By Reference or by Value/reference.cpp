// Можно указать письмо, если его нужно отправить по дороге в магазин.
// Но это необязательно:
void GoToShop(Shop& destination, const vector<Food>& shopping_list, 
              std::optional<Letter> letter_to_send = std::nullopt);
/*
Однако передать через optional объект по ссылке не так просто — для
этого придётся обернуть её в std::reference_wrapper. В h-файле подобная
декларация может выглядеть слишком перегружено, например:
std::optional<std::reference_wrapper<Letter>>. Есть соблазн заменить 
std::reference_wrapper на обычный указатель, чтобы упростить сигнатуру
до такой: std::optional<const Letter*>. Это выглядит лучше, но в таком
случае optional не нужен, ведь как указатель можно передать nullptr.
Правильный тип в таком случае const Letter*:
*/

// Можно указать письмо, если его нужно отправить по дороге в магазин.
// Но это необязательно:
void GoToShop(Shop& destination, const vector<Food>& shopping_list, 
              const Letter* letter_to_send = std::nullptr); 
