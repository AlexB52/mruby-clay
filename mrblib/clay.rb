module Clay
  def self.ui(**keywords)
    Clay.open_element
    Clay.configure_open_element(**keywords)
    yield if block_given?
    Clay.close_element
  end
end
