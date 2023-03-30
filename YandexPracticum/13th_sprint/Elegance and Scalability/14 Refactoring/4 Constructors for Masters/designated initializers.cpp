/*
Подход 3. Принимать в конструкторе ReadingManager
структуру, созданную с помощью designated initializers
*/

ReadingManager manager(ReadingManagerParams{
    .max_user_count = 10000,
    .max_page_count = 500,
    .cheer_factor = 2 }
);

/*
Возможность явно указывать названия полей снижает 
вероятность ошибки и не требует создания Set-методов:
*/
