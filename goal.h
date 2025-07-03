class Goal {
    public:
        Vector2 pos;
        Goal(int, int);

        void draw();
};

Goal::Goal(int x, int y) {
    pos.x = x * D;
    pos.y = y * D;
}
