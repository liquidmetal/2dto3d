#ifndef GLUTAPP_H
#define GLUTAPP_H


class GlutApp
{
        public:
                int win_x,win_y;
                GlutApp(int& argc,char* argv[]);
                virtual ~GlutApp();
                void init();
                void draw();
        protected:
        private:
};

#endif // GLUTAPP_H
