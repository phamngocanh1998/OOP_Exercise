#include "application.h"
#include "polinom.h"
#include "rational.h"
#include "common.h"

QByteArray& operator >>(QByteArray& arr, int& c)
{
    int p = arr.indexOf(separator);
    if (p > 0)
    {
        c = atoi(arr.left(p));
        arr = arr.right(arr.length()- p -1);
    }
    return arr;
}
QString& operator <<(QString& s, int c){
    s+= QString().setNum(c);
    return s;
}

TApplication::TApplication(int argc, char *argv[]): QCoreApplication(argc,argv)
{
    TCommParams pars = {QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm,SIGNAL(received(QByteArray)),this,SLOT(receive(QByteArray)));
}

void TApplication::receive(QByteArray msg)
{
    QString answer, s;
    int pos = msg.indexOf(separator);
    int mode = msg.left(pos).toInt();
    msg = msg.right(msg.length() - pos - 1);
    if(mode == R_MODE){
    TRational a, b, c, x, v;
    msg >> a >> b >> c;
    Polinom<TRational> p(a,b,c);
    pos = msg.indexOf(separator);
    int t = msg.left(pos).toInt();
    switch (t)
    {
        case VALUE_REQUEST:  
        {
            msg = msg.right(msg.length()-pos-1);
            msg >> x;

            if (a.get_value_b() == 0 || b.get_value_b() == 0 || c.get_value_b() == 0 || x.get_value_b() == 0)
            {
                s += "Denominator cant be 0. Reenter.";
                answer << QString().setNum(ERROR) << s;
            }
            else
            {
                if (a.get_value_a() == 0)
                {
                    s += "Value of 'a' cant be 0! Reenter coefficients!";
                    answer << QString().setNum(ERROR) << s;
                }
                else
                {
                    v = p.value(x);
                    s << QString(x) << QString(v);
                    answer << QString().setNum(VALUE_ANSWER);
                    answer += s;
                }
            }
        }
            break;

        case PRINT_CLASSIC_REQUEST:
        {
            if (a.get_value_b() == 0 || b.get_value_b() == 0 || c.get_value_b() == 0 || x.get_value_b() == 0)
            {
                s += "Denominator cant be 0. Reenter.";
                answer << QString().setNum(ERROR) << s;
            }
            else
            {
                if (a.get_value_a() == 0)
                {
                    s += "Value of 'a' cant be 0! Reenter coefficients!";
                    answer << QString().setNum(ERROR) << s;
                }
                else
                {
                    p.setPrintMode(EPrintModeClassic);
                    s<<p;
                    answer<<QString().setNum(PRINT_ANSWER)<<s;
                }
            }
        }
            break;

        case PRINT_CANONIC_REQUEST:
        {
            if (a.get_value_b() == 0 || b.get_value_b() == 0 || c.get_value_b() == 0 || x.get_value_b() == 0)
            {
                s += "Denominator cant be 0. Reenter.";
                answer << QString().setNum(ERROR) << s;
            }
            else
            {
                if (a.get_value_a() == 0)
                {
                    s += "Value of 'a' cant be 0! Reenter coefficients!";
                    answer << QString().setNum(ERROR) << s;
                }
                else
                {
                    p.setPrintMode(EPrintModeCanonic);
                    s << p;
                    answer << QString().setNum(PRINT_ANSWER)<<s;
                }
            }
        }
        break;

        case ROOT_REQUEST:
        {
            if (a.get_value_b() == 0 || b.get_value_b() == 0 || c.get_value_b() == 0 || x.get_value_b() == 0)
            {
                s += "Denominator cant be 0. Reenter.";
                answer << QString().setNum(ERROR) << s;
            }
            else
            {
                if (a.get_value_a() == 0)
                {
                    s += "Value of 'a' cant be 0! Reenter coefficients!";
                    answer << QString().setNum(ERROR) << s;
                }
                else
                {
                    TRational roots[2];
                    int numroots = p.roots(roots);
                    if (numroots == 0)
                        s += "The equation has no solutions!";
                    else
                    {
                        if (numroots == 1)
                        {
                            s += "The equation has one solution: x1 = ";
                            s << roots[0];
                        }
                        else
                        {
                            s += "The equation has two solutions: x1 = ";
                            s << roots[0];
                            s += ", x2 = ";
                            s << roots[1];
                        }
                    }
                    answer << QString().setNum(ROOT_ANSWER) << s;
                }
            }
        }
            break;

        default:
            return;
      }
    }
    else{
        int a, b, c, x, v;
        msg >> a >> b >> c;
        Polinom<int> p(a,b,c);
        pos = msg.indexOf(separator);
        int t = msg.left(pos).toInt();
        switch (t)
        {
            case VALUE_REQUEST:
            {
                msg = msg.right(msg.length()-pos-1);
                msg >> x;
                if (a== 0)
                {
                        s += "Value of 'a' cant be 0! Reenter coefficients!";
                        answer << QString().setNum(ERROR) << s;
                }
                else
                 {
                        v = p.value(x);
                        s << QString().setNum(x); s<< QString().setNum(v);
                        answer << QString().setNum(VALUE_ANSWER);
                        answer += s;
                }
              }

                break;

            case PRINT_CLASSIC_REQUEST:
            {
            if (a== 0)
            {
                    s += "Value of 'a' cant be 0! Reenter coefficients!";
                    answer << QString().setNum(ERROR) << s;
            }
            else
             {
                   p.setPrintMode(EPrintModeClassic);
                   s<<p;
                   answer<<QString().setNum(PRINT_ANSWER)<<s;

              }
            }
                break;

            case PRINT_CANONIC_REQUEST:
            {
            if (a== 0)
            {
                    s += "Value of 'a' cant be 0! Reenter coefficients!";
                    answer << QString().setNum(ERROR) << s;
            }
            else
             {
                     p.setPrintMode(EPrintModeCanonic);
                     s << p;
                     answer << QString().setNum(PRINT_ANSWER)<<s;

            }
        }
            break;

            case ROOT_REQUEST:
            {
            if (a== 0)
            {
                    s += "Value of 'a' cant be 0! Reenter coefficients!";
                    answer << QString().setNum(ERROR) << s;
            }
            else
             {
                        int roots[2];
                        int numroots = p.roots(roots);
                        if (numroots == 0)
                            s += "The equation has no solutions!";
                        else
                        {
                            if (numroots == 1)
                            {
                                s += "The equation has one solution: x1 = ";
                                s << roots[0];
                            }
                            else
                            {
                                s += "The equation has two solutions: x1 = ";
                                s << roots[0];
                                s += ", x2 = ";
                                s << roots[1];
                            }
                        }
                        answer << QString().setNum(ROOT_ANSWER) << s;
                    }
                }
                break;

            default:
                return;
          }
     }
    comm->send(QByteArray().append(answer));
}
