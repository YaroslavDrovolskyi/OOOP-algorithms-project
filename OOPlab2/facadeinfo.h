/**!
  *     \file
  *     \brief header file with declaration of interface abstrFacadeInfo and class concreteFacadeInfo
*/



#ifndef FACADEINFO_H
#define FACADEINFO_H
#include <QString>



/**!
  *     \brief Interface for class that can contain algo results
  *
*/
class abstrFacadeInfo
{
public:

   virtual void setTime(QString t)=0;
   virtual void setName(QString n)=0;
   virtual void setResult(QString s)=0;
   virtual void setCounter(uint32_t c)=0;

    virtual QString getTime() const =0;
    virtual QString getName() const =0;
    virtual QString getResult() const =0;
    virtual uint32_t getCounter() const =0;
   virtual ~abstrFacadeInfo()=default;

};


/**!
  *     \brief Class that contain information about algo running
  *     It has getters and setters for corresponding result fields
  *
*/
class concreteFacadeInfo:public abstrFacadeInfo
{
public:

    concreteFacadeInfo() = default;
    concreteFacadeInfo(QString time, QString name, QString result, uint32_t counter);
    void setTime(QString t) override;
    void setName(QString n)override;
    void setResult(QString s)override;
    void setCounter(uint32_t c) override;


    virtual QString getTime() const override;
    virtual QString getName() const override;
    virtual QString getResult() const override;
    virtual uint32_t getCounter() const override;

    private:
        QString time="";
        QString name="";
        QString result="";
        uint32_t counter=0;



};



#endif // FACADEINFO_H
