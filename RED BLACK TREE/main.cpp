#include<bits/stdc++.h>
using namespace std;

class Redblack
{
public:
    int data;
    Redblack *right,*left,*parent;
    string color;
    Redblack (int data)
    {
        this->data=data;
        parent=left=right=NULL;
        this->color="RED";
    }
};
class RBT
{
public:
    Redblack *root;
    RBT()
    {
        root=NULL;
    }

    Redblack *Insert_node(Redblack *root, Redblack *newnode)
    {
        if(root==NULL)
        {
            return newnode;
        }

        else if(newnode->data<root->data)
        {
            root->left=Insert_node(root->left,newnode);
            root->left->parent=root;
        }
        else
        {
            root->right=Insert_node(root->right,newnode);
            root->right->parent=root;
        }
        return root;
    }

    Redblack *rotate_right(Redblack *root,Redblack *x)
    {
        Redblack *leftchild_of_x=x->left;

        x->left=leftchild_of_x->right;

        if (x->left != NULL)
        {
            x->left->parent = x;
        }
        leftchild_of_x->parent=x->parent;

        if(x->parent==NULL)
        {
            root=leftchild_of_x;
        }
        else if(x==x->parent->left)
        {
            x->parent->left=leftchild_of_x;
        }
        else
        {
            x->parent->right=leftchild_of_x;
        }
        leftchild_of_x->right=x;
        x->parent=leftchild_of_x;
        return root;
    }

    Redblack *rotate_left(Redblack *root, Redblack *x)
    {
        Redblack *rightchild_of_x=x->right;

        x->right=rightchild_of_x->left;

        if(x->right!=NULL)
        {
            x->right->parent=x;
        }
        rightchild_of_x->parent=x->parent;

        if (x->parent == NULL)
        {
            root = rightchild_of_x;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = rightchild_of_x;
        }
        else
        {
            x->parent->right = rightchild_of_x;
        }
        rightchild_of_x->left = x;
        x->parent = rightchild_of_x;
        return root;

    }

    Redblack *fix_the_tree(Redblack *root, Redblack *item)
    {
        Redblack *parrent_of_item=NULL;
        Redblack *gp_of_item=NULL;

        while((item!=root) && (item->parent->color=="RED") && (item->color=="RED"))
        {
            parrent_of_item=item->parent;
            gp_of_item=parrent_of_item->parent;

            if(parrent_of_item==gp_of_item->left)
            {
                Redblack *uncle=gp_of_item->right;

                if(uncle!=NULL && uncle->color=="RED")
                {
                    parrent_of_item->color="BLACK";
                    uncle->color="BLACK";
                    gp_of_item->color="RED";
                    item=gp_of_item;
                }
                else
                {
                    if(item==parrent_of_item->right)
                    {
                        root=rotate_left(root,parrent_of_item);
                        item=parrent_of_item;
                        parrent_of_item=item->parent;
                    }

                    if(item==parrent_of_item->left)
                    {
                        root=rotate_right(root,gp_of_item);
                        swap(gp_of_item->color, parrent_of_item->color);
                        item=parrent_of_item;
                    }
                }
            }
            else
            {
                Redblack *uncle=gp_of_item->left;


                if(uncle!=NULL && uncle->color=="RED")
                {
                    parrent_of_item->color="BLACK";
                    uncle->color="BLACK";
                    gp_of_item->color="RED";
                    item=gp_of_item;
                }

                else
                {
                    if(item==parrent_of_item->left)
                    {
                        root=rotate_right(root,parrent_of_item);
                        item=parrent_of_item;
                        parrent_of_item=item->parent;
                    }
                    if(item==parrent_of_item->right)
                    {

                        root=rotate_left(root,gp_of_item);

                        swap(parrent_of_item->color,gp_of_item->color);

                        item=parrent_of_item;


                    }
                }
            }

        }
        root->color="BLACK";
        return root;
    }


    Redblack *Insert(int element)
    {
        Redblack *newn=new Redblack(element);
        root=Insert_node(root, newn);
        root=fix_the_tree(root,newn);
        return root;
    }
    void pre_order(Redblack *root)
    {
        if (root == NULL)
        {
            return ;
        }
        else
        {
            cout << root->data <<" "<<"{"<<root->color<<"}  ";
            pre_order(root->left);
            pre_order(root->right);
        }
    }

    void post_order(Redblack *root)
    {
        if (root == NULL)
        {
            return ;
        }
        else
        {
            post_order(root->left);
            post_order(root->right);
            cout << root->data <<" "<<"{"<<root->color<<"}  ";
        }
    }
    void in_order(Redblack *root)
    {
        if (root == NULL)
        {
            return ;
        }
        else
        {
            in_order(root->left);
            cout << root->data <<" "<<"{"<<root->color<<"}  ";
            in_order(root->right);
        }
    }
    int find_Max(Redblack *fin)
    {
        while(fin->right!=NULL)
        {
            fin=fin->right;
        }
        return fin->data;

    }
    int find_Min(Redblack *fin)
    {
        while(fin->left!=NULL)
        {
            fin=fin->left;
        }
        return fin->data;
    }


    Redblack *Sibling(Redblack *db)
    {

        Redblack *parent=db->parent;
        if (parent == NULL)
        {
            return NULL;
        }

        if (db==parent->left)
        {
            return parent->right;
        }
        else
        {
            return parent->left;
        }
    }

    Redblack *Redchild(Redblack *x)
    {
        if((x->left!=NULL) && (x->left->color=="RED"))
        {
            return x->left;
        }
        else if((x->right!=NULL) && (x->right->color=="RED"))
        {
            return x->right;
        }
        else
        {
            return NULL;
        }
    }

    bool Check_f_RC(Redblack *db, Redblack *sibling, Redblack *rc, Redblack *parent)
    {
        if((db==parent->right && rc==sibling->left)|| (db==parent->left && rc==sibling->right))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Redblack *fix_double_black(Redblack *root,Redblack *db)
    {
        Redblack *sibling=Sibling(db);
        Redblack  *parent=db->parent;

        if(db==root)
        {
            return root;
        }
        if(sibling==NULL)
        {
            if(parent->color=="RED")
            {
                parent->color="black";
            }
            if(parent->color=="BLACK") root=fix_double_black(root,parent);
            return root;
        }
        else if(sibling->color=="BLACK")
        {
            Redblack *rc=Redchild(sibling);
            if(rc==NULL)
            {
                if(parent->color=="RED")
                {
                    parent->color="BLACK";
                    sibling->color="RED";
                    return root;
                }
                if(parent->color=="BLACK")
                {
                    sibling->color="RED";
                    root=fix_double_black(root,parent);
                    return root;
                }
            }
            else if(Check_f_RC(db,sibling,rc,parent))
            {
                swap(parent->color,sibling->color);
                if(db==parent->right)
                {
                    root=rotate_right(root, parent);
                }
                else
                {
                    root=rotate_left(root,parent);
                }
                rc->color="BLACK";
                return root;
            }
            else
            {
                swap(sibling->color, rc->color);
                if(db==parent->right){
                        root=rotate_left(root,sibling);
                }

                else {
                        root=rotate_right(root,sibling);
                }
                root=fix_double_black(root,db);
                return root;
            }
        }
        else if(sibling->color=="RED")
        {
            swap(parent->color,sibling->color);
            if(db==parent->left){
                    root=rotate_left(root,parent);
            }
            else{
                    root=rotate_right(root,parent);
            }
            root=fix_double_black(root,db);

            return root;
        }

    }


    Redblack *Delete(Redblack *root, Redblack *temp, int value)
    {
        if(temp!=NULL)
        {
            if(value<temp->data)
            {
                root=Delete(root,temp->left,value);
            }
            else if(value>temp->data)
            {
                root=Delete(root,temp->right,value);
            }
            else
            {

                if(temp->left==NULL && temp->right==NULL)
                {
                    Redblack *temp2=temp;
                    if(temp->color=="BLACK")
                    {
                        root=fix_double_black(root,temp);

                    }

                    if(temp->parent->right==temp) temp->parent->right=NULL;
                    else if(temp->parent->left==temp) temp->parent->left=NULL;
                    delete(temp2);
                    return root;
                }

                if(temp->left==NULL && temp->right!=NULL)
                {

                    int mnv=find_Min(temp->right);
                    temp->data=mnv;
                    root=Delete(root,temp->right,mnv);
                }
                if(root->right==NULL && root->left!=NULL)
                {
                    int mxv=find_Max(temp->left);
                    temp->data=mxv;
                    root=Delete(root,temp->left,mxv);

                }


                else if(root->right!=NULL && root->left!=NULL)
                {
                    int mxv=find_Max(temp->left);
                    temp->data=mxv;
                    root=Delete(root,temp->left,mxv);
                }

            }
        }
        return root;
    }


    Redblack *Search(Redblack *root1, int value)
    {
        while(root1!=NULL)
        {
            if(root1->data== value)
            {
                return root1;
            }
            else if(value<root1->data)
            {
                return Search(root1->left,value);
            }
            else if(value >root1->data)
            {
                return Search(root1->right,value);
            }
            return NULL;
        }
    }

    Redblack *deleteByValue(Redblack *root,int n)
    {
        if(root==NULL)
        {
            return root;
        }
        Redblack *ans=Search(root,n);

        if(ans==NULL)
        {
            cout<<"NOT FOUND!! "<<n<<endl;
            return root;
        }


        root=Delete(root,root,n);
        return root;

    }


};


int main()
{

    RBT *redblack=new RBT();

    bool f= false;
    char r;
    int x,x1,x2;
    struct node *root = NULL;
    struct node *root1 = NULL;
    struct node *temp1= NULL;
    struct node *temp2= NULL;
    while(true)
    {
    cout<<"A.Insert"<<endl;
    cout<<"B.Pre order"<<endl;
    cout<<"C.In order"<<endl;
    cout<<"D.Post order"<<endl;
    cout<<"E.Find maximum element"<<endl;
    cout<<"F.Find minimum elememt"<<endl;
    cout<<"G.Search"<<endl;
    cout<<"H.Delete"<<endl;
    cout<<"I.Exit"<<endl<<endl;

    cout<<"Please Enter an choice:"<<endl;
        cin>>r;
        if(r=='A')
        {
            cout<<"Please enter the value:"<<endl;
            cin>>x;
            redblack->root=redblack->Insert(x);
        }
        else if(r=='B')
        {
            redblack->pre_order(redblack->root);
            cout<<endl<<endl;
            break;

        }
        else if(r=='C')
        {
            redblack->in_order(redblack->root);
            cout<<endl<<endl;
        }
        else if(r=='D')
        {

            redblack->post_order(redblack->root);
            cout<<endl<<endl;
        }
        else if(r=='E')
        {
            int m=redblack->find_Max(redblack->root);
            cout<<"The maximum value of the tree is: "<<m<<endl;
        }
        else if(r=='F')
        {
            int m=redblack->find_Min(redblack->root);
            cout<<"The minimum value of the tree is: "<<m<<endl<<endl;
        }
        else if(r=='G')
        {
            cout<<"Please enter which element do you want to search for: ";
            cin>>x1;
            Redblack *ans=redblack->Search(redblack->root,x1);
            if(ans==NULL)
            {
                cout<<"NOT FOUND!!"<<endl;

            }
            else{
                    cout<<"FOUNDED! THE ELEMENT IS:  "<<x1<<endl;
            }
        }
        else if (r=='H')
        {
            cout<<"Please Enter the value:"<<endl;
            cin>>x;
            redblack->root=redblack->deleteByValue(redblack->root,x);

        }
        if(r=='I')
        {
            f=false;
            break;
        }

    }
}
