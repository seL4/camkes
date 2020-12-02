/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes.h>
#include <camkes/error.h>
#include "ctypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char lorem[] = "In publishing and graphic design, placeholder text is commonly used to demonstrate the elements of a document or visual presentation, such as font, typography, and layout. Even though using \"lorem ipsum\" often arouses curiosity because of its resemblance to classical Latin, it is not intended to have meaning. Where text is visible in a document, people tend to focus on the textual content rather than upon overall presentation, so publishers use lorem ipsum when displaying a typeface or design elements and page layout in order to direct the focus to the publication style and not the meaning of the text.\n"
"\n"
"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Itaque illa non dico me expetere, sed legere, nec optare, sed sumere, contraria autem non fugere, sed quasi secernere. In omni enim arte vel studio vel quavis scientia vel in ipsa virtute optimum quidque rarissimum est. An quae de prudentia, de cognitione rerum, de coniunctione generis humani, quaeque ab eisdem de temperantia, de modestia, de magnitudine animi, de omni honestate dicuntur? Duo Reges: constructio interrete. Est enim perspicuum nullam artem ipsam in se versari, sed esse aliud artem ipsam, aliud quod propositum sit arti. Ita, quae mutat, ea corrumpit, quae sequitur sunt tota Democriti, atomi, inane, imagines, quae eidola nominant, quorum incursione non solum videamus, sed etiam cogitemus; Neque enim disputari sine reprehensione nec cum iracundia aut pertinacia recte disputari potest. Quae quidem vel cum periculo est quaerenda vobis; Ut iam liceat una comprehensione omnia complecti non dubitantemque dicere omnem naturam esse servatricem sui idque habere propositum quasi finem et extremum, se ut custodiat quam in optimo sui generis statu; Idque si ita dicit, non esse reprehendendos luxuriosos, si sapientes sint, dicit absurde, similiter et si dicat non reprehendendos parricidas, si nec cupidi sint nec deos metuant nec mortem nec dolorem. Quid dubitas igitur, inquam, summo bono a te ita constituto, ut id totum in non dolendo sit, id tenere unum, id tueri, id defendere? Unum, cum in voluptate sumus, alterum, cum in dolore, tertium hoc, in quo nunc equidem sum, credo item vos, nec in dolore nec in voluptate; Quanta autem ab illis varietas argumentorum ratione concludentium eorumque cum captiosis interrogationibus dissimilitudo! Quid, quod plurimis locis quasi denuntiant, ut neque sensuum fidem sine ratione nec rationis sensibus exquiramus? Alterum autem genus est magnarum verarumque virtutum, quas appellamus voluntarias, ut prudentiam, temperantiam, fortitudinem, iustitiam et reliquas eiusdem generis.\n"
"\n"
"Naturalem enim appetitionem, quam vocant o)rmh)n, itemque officium, ipsam etiam virtutem tuentem volunt esse earum rerum, quae secundum naturam sunt. Quamquam ex omnibus philosophis Stoici plurima novaverunt, Zenoque, eorum princeps, non tam rerum inventor fuit quam verborum novorum. Et qui ipsi sibi bellum indixissent, cruciari dies, noctes torqueri vellent, nec vero sese ipsi accusarent ob eam causam, quod se male suis rebus consuluisse dicerent. Sunt enim prima elementa naturae, quibus auctis vírtutis quasi germen efficitur. Qualis est igitur omnis haec, quam dico, conspiratio consensusque virtutum, tale est illud ipsum honestum, quandoquidem honestum aut ipsa virtus est aut res gesta virtute; Quoniamque in iis rebus, quae neque in virtutibus sunt neque in vitiis, est tamen quiddam, quod usui possit esse, tollendum id non est. Etsi ea quidem, quae adhuc dixisti, quamvis ad aetatem recte isto modo dicerentur. Haec mihi videtur delicatior, ut ita dicam, molliorque ratio, quam virtutis vis gravitasque postulat. Eam si varietatem diceres, intellegerem, ut etiam non dicente te intellego; Hanc se tuus Epicurus omnino ignorare dicit quam aut qualem esse velint qui honestate summum bonum metiantur. Sed certe opus est ea valere et vigere et naturales motus ususque habere, ut nec absit quid eorum nec aegrum debilitatumve sit; Primum non saepe, deinde quae est ista relaxatio, cum et praeteriti doloris memoria recens est et futuri atque inpendentis torquet timor? Hinc est illud exortum, quod Zeno prohgmšnon, contraque quod époprohgmšnon nominavit, cum uteretur in lingua copiosa factis tamen nominibus ac novis, quod nobis in hac inopi lingua non conceditur; Ipse negat, ut ante dixi, luxuriosorum vitam reprehendendam, nisi plane fatui sint, id est nisi aut cupiant aut metuant. Sed et illum, quem nominavi, et ceteros sophistas, ut e Platone intellegi potest, lusos videmus a Socrate.\n"
"\n"
"Completur enim et ex eo genere vitae, quod virtute fruitur, et ex iis rebus, quae sunt secundum naturam neque sunt in nostra potestate. Quid enim dicis omne animal, simul atque sit ortum, applicatum esse ad se diligendum esseque in se conservando occupatum? Reicietur etiam Carneades, nec ulla de summo bono ratio aut voluptatis non dolendive particeps aut honestatis expers probabitur. Iam ille sorites, quo nihil putatis esse vitiosius: quod bonum sit, id esse optabile, quod optabile, id expetendum, quod expetendum, id laudabile, deinde reliqui gradus. Quis tibi ergo istud dabit praeter Pyrrhonem, Aristonem eorumve similes, quos tu non probas? Ergo in gubernando nihil, in officio plurimum interest, quo in genere peccetur. Equidem in omnibus istis conclusionibus hoc putarem philosophia nobisque dignum, et maxime, cum summum bonum quaereremus, vitam nostram, consilia, voluntates, non verba corrigi. Non ego tecum iam ita iocabor, ut isdem his de rebus, cum L. Utrum igitur tibi non placet, inquit, virtutisne tantam esse vim, ut ad beate vivendum se ipsa contenta sit? Non enim, si malum est dolor, carere eo malo satis est ad bene vivendum.\n"
"\n"
"Torquatus, is qui consul cum Cn. Quae enim dici Latine posse non arbitrabar, ea dicta sunt a te verbis aptis nec minus plane quam dicuntur a Graecis. Omnesque eae sunt genere quattuor, partibus plures, aegritudo, formido, libido, quamque Stoici communi nomine corporis et animi don appellant, ego malo laetitiam appellare, quasi gestientis animi elationem voluptariam. Iam ille sorites, quo nihil putatis esse vitiosius: quod bonum sit, id esse optabile, quod optabile, id expetendum, quod expetendum, id laudabile, deinde reliqui gradus. Et quis a Stoicis et quem ad modum diceretur, tamen ego quoque exponam, ut perspiciamus, si potuerimus, quidnam a Zenone novi sit allatum. Modo enim fuit Carneadis, quem videre videor-est, enim nota imago -, a sedeque ipsa tanta ingenii, magnitudine orbata desiderari illam vocem puto. Minime vero probatur huic disciplinae, de qua loquor, aut iustitiam aut amicitiam propter utilitates adscisci aut probari. Atque omnia quidem scire, cuiuscumque modi sint, cupere curiosorum, duci vero maiorum rerum contemplatione ad cupiditatem scientiae summorum virorum est putandum. Et certamen honestum et disputatio splendida! omnis est enim de virtutis dignitate contentio. Ita, quae mutat, ea corrumpit, quae sequitur sunt tota Democriti, atomi, inane, imagines, quae eidola nominant, quorum incursione non solum videamus, sed etiam cogitemus; Itaque eos id agere, ut a se dolores, morbos, debilitates repellant. Duo enim genera quae erant, fecit tria.\n"
"\n"
"Quis est autem dignus nomine hominis, qui unum diem totum velit esse in genere isto voluptatis? Itaque ut quisque optime natus institutusque est, esse omnino nolit in vita, si gerendis negotiis orbatus possit paratissimis vesci voluptatibus. Sunt enim quasi prima elementa naturae, quibus ubertas orationis adhiberi vix potest, nec equidem eam cogito consectari. Qui cum praetor quaestionem inter sicarios exercuisset, ita aperte cepit pecunias ob rem iudicandam, ut anno proximo P. Qua tu etiam inprudens utebare non numquam. Licet hic rursus ea commemores, quae optimis verbis ab Epicuro de laude amicitiae dicta sunt. Itaque e contrario moderati aequabilesque habitus, affectiones ususque corporis apti esse ad naturam videntur. Nam hunc ipsum sive finem sive extremum sive ultimum definiebas id esse, quo omnia, quae recte fierent, referrentur neque id ipsum usquam referretur. Quae dici eadem de ceteris virtutibus possunt, quarum omnium fundamenta vos in voluptate tamquam in aqua ponitis. Quod autem satis est, eo quicquid accessit, nimium est;\n";

static unsigned int overrun_errors;
static unsigned int other_errors;

static camkes_error_action_t handler(camkes_error_t *error) {
    if (error->type == CE_BUFFER_LENGTH_EXCEEDED) {
        overrun_errors++;
    } else {
        other_errors++;
    }
    return CEA_DISCARD;
}

int run(void) {
    static_assert(sizeof(lorem) >= PAGE_SIZE_4K * 2,
        "text not large enough to probe dataport behaviour");

    printf("Testing basic one page dataport...\n");
    static char s1[PAGE_SIZE_4K];
    memcpy(s1, lorem, sizeof(s1) - 1);
    s1[sizeof(s1) - 1] = '\0';
    char *ret = b_echo(s1);
    assert(strcmp(s1, ret) == 0);
    free(ret);

    printf("Test overwriting basic one page dataport...\n");
    overrun_errors = 0;
    other_errors = 0;
    b_register_error_handler(handler);
    static char s1a[PAGE_SIZE_4K + 1];
    memcpy(s1a, lorem, sizeof(s1a) - 1);
    s1a[sizeof(s1a) - 1] = '\0';
    ret = b_echo(s1a);
    assert(overrun_errors == 1);
    assert(other_errors == 0);
    b_register_error_handler(NULL);

    printf("Testing larger two page aligned dataport...\n");
    static char s3[PAGE_SIZE_4K * 2];
    memcpy(s3, lorem, sizeof(s3) - 1);
    s3[sizeof(s3) - 1] = '\0';
    ret = f_echo(s3);
    assert(strcmp(s3, ret) == 0);
    free(ret);

    printf("Test overwriting larger two page aligned dataport...\n");
    overrun_errors = 0;
    other_errors = 0;
    f_register_error_handler(handler);
    static char s3a[PAGE_SIZE_4K * 2 + 1];
    memcpy(s3a, lorem, sizeof(s3a) - 1);
    s3a[sizeof(s3a) - 1] = '\0';
    ret = f_echo(s3a);
    assert(overrun_errors == 1);
    assert(other_errors == 0);
    f_register_error_handler(NULL);

    printf("Testing C struct dataport...\n");
    static char s4[sizeof(CStruct)];
    memcpy(s4, lorem, sizeof(s4) - 1);
    s4[sizeof(s4) - 1] = '\0';
    ret = h_echo(s4);
    assert(strcmp(s4, ret) == 0);
    free(ret);

    printf("Test overwriting C struct dataport...\n");
    overrun_errors = 0;
    other_errors = 0;
    h_register_error_handler(handler);
    static char s4a[sizeof(CStruct) + 1];
    memcpy(s4a, lorem, sizeof(s4a) - 1);
    s4a[sizeof(s4a) - 1] = '\0';
    ret = h_echo(s4a);
    assert(overrun_errors == 1);
    assert(other_errors == 0);
    h_register_error_handler(NULL);

    printf("Testing two page C struct dataport...\n");
    static char s5[sizeof(CStructBig)];
    memcpy(s5, lorem, sizeof(s5) - 1);
    s5[sizeof(s5) - 1] = '\0';
    ret = j_echo(s5);
    assert(strcmp(s5, ret) == 0);
    free(ret);

    printf("Test overwriting two page C struct dataport...\n");
    overrun_errors = 0;
    other_errors = 0;
    j_register_error_handler(handler);
    static char s5a[sizeof(CStructBig) + 1];
    memcpy(s5a, lorem, sizeof(s5a) - 1);
    s5a[sizeof(s5a) - 1] = '\0';
    ret = j_echo(s5a);
    assert(overrun_errors == 1);
    assert(other_errors == 0);
    j_register_error_handler(NULL);

    printf("All OK\n");

    return 0;
}
