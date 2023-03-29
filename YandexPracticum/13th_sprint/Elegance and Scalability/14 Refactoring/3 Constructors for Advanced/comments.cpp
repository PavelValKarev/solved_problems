//вызов конструктора с непонятными параметрами
ReadingManager manager(20000, 1000, 2);

//чтобы внести ясность можно добавить комментарии
ReadingManager manager(
	/* max_user_count */ 20000,
	/* max_page_count */ 1000,
	/* cheer_factor */   2);
