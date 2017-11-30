<?php

namespace Drupal\omf_redirect\Controller;

use Symfony\Component\HttpFoundation\RedirectResponse;


class OMFRedirect {
  function auctionPage() {
     return new RedirectResponse('http://www.ebay.com/sch/openmediafoundation/m.html?_nkw=&_armrs=1&_ipg=&_from=&rt=nc&LH_Auction=1');
  }
}
